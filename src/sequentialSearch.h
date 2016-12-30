/*
 * sequentialSearch.h
 *
 *  Created on: 22/12/2016
 *      Author: beatrizHm
 */

#ifndef SEQUENTIALSEARCH_H_
#define SEQUENTIALSEARCH_H_

#include <vector>
using namespace std;

template<class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x) {
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i] == x) {
			return i;   // encontrou
		}
	}
	return -1;     // n�o encontrou
}

#endif /* SEQUENTIALSEARCH_H_ */
