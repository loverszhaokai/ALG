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
 * This file contains the floyd algorithm
 */

#include "dijkstra.h"

void floyd(const int **matrix, const int N, int **out)
{
	// Copy matrix to out
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			out[iii][jjj] = matrix[iii][jjj];

	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			for (int kkk = 0; kkk < N; kkk++)
				if (jjj != kkk &&
					out[jjj][kkk] > out[jjj][iii] + out[iii][kkk])
					out[jjj][kkk] = out[jjj][iii] + out[iii][kkk];
}

void floyd_dijkstra(const int **matrix, const int N, int **out)
{
	int dist[N];

	for (int iii = 0; iii < N; iii++) {
		dijkstra_wiki(matrix, N, iii, dist);
		for (int jjj = 0; jjj < N; jjj++)
			out[jjj][iii] = out[iii][jjj] = dist[jjj];
	}
}
