/*
 * ALG
 * --------------------------------
 *
 * Copyright 2016 Kai Zhao <loverszhao@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * This file contains the dijkstra algorithm
 */

#include <algorithm>
#include <list>

#include "../test/matrix.h"

using std::list;

/*
 * Reference: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 * Here we do not use the priority queue
 *
 * @dist: Record the current distance from start to each vertex
 */
void dijkstra_wiki(const int **matrix, const int N, const int start, int *dist)
{
	// The current smallest distance between start and other vertex
	int min_dist;
	// The vertex of min_dist
	int min_dist_v;
	// Record whether the vertex is visited
	int is_visited[N];

	for (int iii = 0; iii < N; iii++) {
		dist[iii] = matrix[start][iii];
		is_visited[iii] = 0;
	}

	is_visited[start] = 1;

	while (1) {

		// Find the minimum distance vertex
		min_dist_v = -1;
		for (int iii = 0; iii < N; iii++) {

			if (dist[iii] == MAX_VALUE || is_visited[iii])
				continue;

			if (min_dist_v == -1) {
				min_dist_v = iii;
				min_dist = dist[iii];
			} else if (dist[iii] < min_dist) {
				min_dist_v = iii;
				min_dist = dist[iii];
			}
		}

		// All vertex have been visited
		if (min_dist_v == -1)
			break;

		// Visit a new vertex
		is_visited[min_dist_v] = 1;

		// Try to update not visited dist[N]
		for (int iii = 0; iii < N; iii++) {

			if (is_visited[iii])
				continue;

			if (dist[iii] > min_dist + matrix[min_dist_v][iii])
				dist[iii] = min_dist + matrix[min_dist_v][iii];
		}
	}
}

/*
 * The following algorithm is very slow and it is not based on the
 * original dijkstra algorithm.
 * Calculate the smallest distance from start to other positions
 */
void shortest_path_kai(const int **matrix, const int N, const int start, int *dist)
{
	int is_visited[N];
	list<int> indexs;

	for (int iii = 0; iii < N; iii++) {
		dist[iii] = matrix[start][iii];
		is_visited[iii] = 0;
	}

	is_visited[start] = 1;
	indexs.push_back(start);

	while (!indexs.empty()) {
		const int v = indexs.front();
		indexs.pop_front();

		for (int iii = 0; iii < N; iii++) {
			if (v == iii || start == iii || matrix[v][iii] == MAX_VALUE)
				continue;

			if (dist[iii] > dist[v] + matrix[v][iii]) {
				dist[iii] = dist[v] + matrix[v][iii];

				// The distance between start and iii is updated, so we should
				// try to update iii's neighbours
				if (std::find(indexs.begin(), indexs.end(), iii) == indexs.end()) {
					is_visited[iii] = 1;

					indexs.push_back(iii);
				}
			}

			if (!is_visited[iii]) {
				is_visited[iii] = 1;
				indexs.push_back(iii);
			}
		}
	}
}
