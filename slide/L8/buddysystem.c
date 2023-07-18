///                MentOS, The Mentoring Operating system project
/// @file buddysystem.c
/// @brief Buddy System.
/// @copyright (c) 2019 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include "buddysystem.h"
#include "debug.h"
#include "assert.h"

/// @brief           Get the buddy index of a page.
/// @param  page_idx A page index.
/// @param  order    The logarithm of the size of the block.
/// @return          The page index of the buddy of page.
static unsigned long get_buddy_idx(unsigned long page_idx, unsigned int order)
{
	//  Get the index of the buddy block.
    //
    //  ----------------------- xor -----------------------
    // | page_idx    ^   (1UL << order)    =     buddy_idx |
    // |     1                  1                    0     |
    // |     0                  1                    1     |
    //  ---------------------------------------------------
    //
    // If the bit of page_idx that corresponds to the block
    // size, is 1, then we have to take the block on the
    // left (0), otherwise we have to take the block on the right (1).
	unsigned long buddy_idx = page_idx ^ (1UL << order);
	return buddy_idx;
}

page_t *bb_alloc_pages(zone_t *zone, unsigned int order)
{
	page_t *page = NULL;
	free_area_t *area = NULL;

	// Cyclic search through each list for an available block,
    // starting with the list for the requested order and
    // continuing if necessary to larger orders.
	unsigned int current_order;
	for (current_order = order; current_order < MAX_ORDER; ++current_order) {
		area = zone->free_area + current_order;

		if (!list_head_empty(&area->free_list)) {
			goto block_found;
		}
	}

	// No suitable free block has been found.
	return NULL;

block_found:
	// Remove the descriptor of its first page frame.
	page = list_entry(area->free_list.next, page_t, lru); // NB: PUNTO COMPLESSO: free_list di struct area e' una lista di page_t
	list_head_del(&page->lru);

	// Set the page allocated, therefore the private field has no meaning.
	page->_count = 0;
	page->private = 0;
	// Decrease the number of free block of the free_area_t.
	area->nr_free--;

	// Found a block of 2^k page frames, to satisfy a request
    // for 2^h page frames (h < k) the program allocates
    // the first 2^h page frames and iteratively reassigns
    // the last 2^k – 2^h page frames to the free_area lists
    // that have indexes between h and k.
	unsigned int size = 1 << current_order;
	while (current_order > order) {
		// Refer to the lower free_area_t and order.
		area--;
		current_order--;

		// Split the block and set free the second half.
		size >>= 1UL;
		page_t *buddy = page + size;
		// Insert buddy as first element in the list.
		list_head_add(&buddy->lru, &area->free_list);
		// Increase the number of free block of the free_area_t.
		area->nr_free++;
		/* buddy has already the _count field set to -1,
         * therefore only save the order of the buddy.
         */
		buddy->private = current_order;
	}

	buddy_system_dump(zone);

	return page;
}

void bb_free_pages(zone_t *zone, page_t *page, unsigned int order)
{
	// Take the first page descriptor of the zone.
	page_t *base = zone->zone_mem_map;
	// Take the page frame index of page compared to the zone.
	unsigned long page_idx = page - base;
	/* Set the page freed, but do not set the private
     * field because we want to try to merge.
     */
	page->_count = -1;

	/* Performs a cycle that starts with the smallest
     * order block and moves up to the top order.
     */
	while (order < MAX_ORDER - 1) {
		// Get the index of the buddy.
		unsigned long buddy_idx = get_buddy_idx(page_idx, order);
		// Return the page descriptor of the buddy.
		page_t *buddy = base + buddy_idx;

		// Check if the buddy is free.
		if (!(buddy->_count == -1 && buddy->private == order)) {
			break;
		}

		/* If buddy is free, remove buddy from the current free list,
         * because than the coalesced block will be inserted on a
         * upper order.
         */
		list_head_del(&buddy->lru);
		// Decrease the number of free block of the current free_area_t.
		zone->free_area[order].nr_free--;

		// buddy no longer represents a free block, so clear the private field.
		buddy->private = 0;

		// Update the page index with the index of the coalesced block.
		//if (page_idx > buddy_idx)
		//	page_idx = buddy_idx
		page_idx &= buddy_idx;

		order++;
	}

	// Take the coalesced block with the order reached up.
	page_t *coalesced = base + page_idx;
	coalesced->private = order;
	// Insert coalesced as first element in the free list.
	list_head_add(&coalesced->lru, &zone->free_area[order].free_list);
	// Increase the number of free block of the free_area_t.
	zone->free_area[order].nr_free++;

	buddy_system_dump(zone);
}

void buddy_system_dump(zone_t *zone)
{
	// Print free_list's size of each area of the zone.
	dbg_print("Zone\t%s\t", zone->name);
	for (int order = 0; order < MAX_ORDER; order++) {
		free_area_t *area = zone->free_area + order;
		dbg_print("%d\t", area->nr_free);
	}
	dbg_print("\n");
}
