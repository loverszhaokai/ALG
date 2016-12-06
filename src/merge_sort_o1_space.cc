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
 * This file contains the sort algorithms, including merge sort.
 */

#include "merge_sort_o1_space.h"

// Reference: http://www.cnblogs.com/daniagger/archive/2012/07/25/2608373.html

//交换两个数
static void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
//将长度为n的数组逆序
static void reverse(int *arr,int n)
{
    int i=0,j=n-1;
    while(i<j)
    {
        swap(&arr[i],&arr[j]);
        i++;
        j--;
    }
}
 
//将数组向左循环移位i个位置
static void exchange(int *arr,int n,int i)
{
    reverse(arr,i);
    reverse(arr+i,n-i);
    reverse(arr,n);
}
 
//数组两个有序部分的归并
static void merge(int *arr,int begin,int mid,int end)
{
    int i=begin,j=mid,k=end;
    while(i<j && j<=k)
    {
        int step=0;
        while(i<j && arr[i]<=arr[j])
            ++i;
        while(j<=k && arr[j]<=arr[i])
        {
            ++j;
            ++step;
        }
        exchange(arr+i,j-i,j-i-step);
        i=i+step;
    }
}
 
void MergeSortO1SpaceImpl(int *arr,int l,int r)
{
    if(l<r)
    {
        int mid=(l+r)/2;
        MergeSortO1SpaceImpl(arr,l,mid);
        MergeSortO1SpaceImpl(arr,mid+1,r);
        merge(arr,l,mid+1,r);
    }
}

void MergeSortO1Space(int *arr,int size)
{
  MergeSortO1SpaceImpl(arr, 0, size - 1);
}
