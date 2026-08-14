import sys
from bisect import bisect_left, bisect_right, insort
from collections import defaultdict, Counter, deque
from heapq import heappush, heappop, heapify
from math import gcd, lcm, isqrt

input = sys.stdin.readline


def solve():
    n = int(input()) #leer numero
    a,b,c= map(int, input().split()) #leer numeros
    s = input().strip() #leer cadenas
    v = list(map(int, input().split())) #leer lista de enteros


t = 1
# t = int(input())
for _ in range(t):
    solve()

# C++                         Python

# vector                      list
# array                       list
# string                      str

# set                         set
# map                         dict
# multiset                    Counter
# unordered_map               dict
# unordered_set               set

# priority_queue              heapq
# queue                       deque
# deque                       deque

# lower_bound                 bisect_left
# upper_bound                 bisect_right
# sort                        list.sort()
# binary_search               bisect_left/right

# pair                        tuple
# struct                      class / dataclass

# gcd                         math.gcd
# lcm                         math.lcm

# push_back                   append
# push_front                  appendleft
# pop_back                    pop
# pop_front                   popleft

# size()                      len()
# empty()                     not x