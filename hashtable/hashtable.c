#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

/* Daniel J. Bernstein's "times 33" string hash function, from comp.lang.C;
   See https://groups.google.com/forum/#!topic/comp.lang.c/lSKWXiuNOAk */
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

hashtable_t *make_hashtable(unsigned long size) {
  hashtable_t *ht = malloc(sizeof(hashtable_t));
  ht->size = size;
  ht->buckets = calloc(size, sizeof(bucket_t *));
  return ht;
}

void ht_put(hashtable_t *ht, char *key, void *val) {
  /* FIXME: the current implementation doesn't update existing entries */
  unsigned int idx = hash(key) % ht->size;
  bucket_t *b = ht->buckets[idx];
  while (b) {
    if (strcmp(b->key, key) == 0) {
      b->val = val;
      return ;
    }
    b = b->next;
  }

  b = malloc(sizeof(bucket_t));
  b->key = key;
  b->val = val;
  b->next = ht->buckets[idx];
  ht->buckets[idx] = b;
}

void *ht_get(hashtable_t *ht, char *key) {
  unsigned int idx = hash(key) % ht->size;
  bucket_t *b = ht->buckets[idx];
  while (b) {
    if (strcmp(b->key, key) == 0) {
      return b->val;
    }
    b = b->next;
  }
  return NULL;
}

void ht_iter(hashtable_t *ht, int (*f)(char *, void *)) {
  bucket_t *b;
  unsigned long i;
  for (i=0; i<ht->size; i++) {
    b = ht->buckets[i];
    while (b) {
      if (!f(b->key, b->val)) {
        return ; // abort iteration
      }
      b = b->next;
    }
  }
}

void free_hashtable(hashtable_t *ht) {
  bucket_t *b, *next;
  unsigned long i;
  for (i = 0; i < ht->size; i++) {
    b = ht->buckets[i];
    while (b) {
      next = b->next;
      free(b->key);
      free(b->val);
      free(b);
      b = next;
    }
  }

  free(ht);
}

/* TODO */
void  ht_del(hashtable_t *ht, char *key) {
  unsigned int idx = hash(key) % ht->size;
  bucket_t *b = ht->buckets[idx],
           *b_last = NULL;
  while (b) {
    if (strcmp(b->key, key) == 0) {
      if (b_last == NULL) {
        ht->buckets[idx] = b->next;
      }
      else {
        b_last->next = b->next;
      }
      free(b);
      return ;
    }
    b_last = b;
    b = b->next;
  }
}

void  ht_rehash(hashtable_t *ht, unsigned long newsize) {
  hashtable_t *new_ht = make_hashtable(newsize);

  // iterate through old table and insert into new
  bucket_t *b, *next;
  unsigned long i;
  for (i = 0; i < ht->size; i++) {
    b = ht->buckets[i];
    while (b) {
      ht_put(new_ht, b->key, b->val);
      next = b->next;
      free(b);
      b = next;
    }
  }

  ht->buckets = new_ht->buckets;
  ht->size = new_ht->size;
  free(new_ht);
}
