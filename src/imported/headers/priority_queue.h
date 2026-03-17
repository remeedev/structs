#ifndef priority_queue
#define priority_queue

#define pq void **

pq create_pq(int max_heap);
int get_pq_size(pq a);

void pq_push(pq a, int priority, void *content);
void pq_push_int(pq a, int priority, int content);
void pq_push_float(pq a, int priority, float content);
void pq_push_double(pq a, int priority, double content);
void* pq_pop(pq a);

void free_pq(pq a);

#endif
