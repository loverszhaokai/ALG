/*
 * ALG
 * --------------------------------
 *
 * Copyright 2015 Kai Zhao
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

using std::list;

/*
 * Calculate the smallest distance from start to other positions
 */
void dijkstra(int **matrix, const int N, const int start)
{
	int is_visited[N];
	list<int> indexs;

	for (int iii = 0; iii < N; iii++)
		is_visited[iii] = 0;

	is_visited[start] = 1;
	indexs.push_back(start);

	while (!indexs.empty()) {
		const int v = indexs.front();
		indexs.pop_front();

		for (int iii = 0; iii < N; iii++) {
			if (v == iii || start == iii || matrix[v][iii] == -1)
				continue;

			if (v != start)
			if (matrix[start][iii] == -1 ||
				matrix[start][v] + matrix[v][iii] < matrix[start][iii]) {

				matrix[start][iii] = matrix[start][v] + matrix[v][iii];
				matrix[iii][start] = matrix[start][iii];

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
