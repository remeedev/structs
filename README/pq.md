# Priority Queue

It's a list, except it must always be somehow organized (??)

## Usage

After including the `priority_queue.h` file into your code you can:

Create a new pq using the following function:

```c
pq new_pq = create_pq(0); // 0 or 1, depending on if you need min heap or max heap
```

The following are the push functions for priority queue:

```c
void pq_push(pq a, int priority, void *content);
void pq_push_int(pq a, int priority, int content);
void pq_push_float(pq a, int priority, float content);
void pq_push_double(pq a, int priority, double content);
```

All functions, except for `pq_push(pq, int, void*);` allocate new space for the element.

Popping a priority queue always pops the first element (Minimum or Maximum depending on the type of heap), to pop an element in the pq one must run:

```c
void *a = pq_pop(pq);
```

It will store in `a` the value with highest/lowest priority in the queue. It will, however, not return the priority of the element.

---

You can also get the size of the priority queue by running:

```c
get_pq_size(pq); // Returns an int with the size
```

---

Finally, when you are done with the queue you must free it by running:

```c
free_pq(pq);
```
