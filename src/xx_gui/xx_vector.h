#define XX_VECTOR 0x0F
#define XX_VECTOR_DEFAULT_CAPACITY 5

typedef struct {
  void* data;
  int item_size;
  int cursor;
  int capacity;
} xx_vector;

xx_vector* xx_create_vector ( int item_size );
void xx_add_to_vector ( xx_vector* vec, void* l_data );
void xx_free_vector ( xx_vector* vec );
void* xx_read_from_vector ( xx_vector* vec, int cur );

xx_vector* xx_create_vector ( int item_size ) {
  xx_vector* vec = (xx_vector*) calloc (sizeof(xx_vector), 1);
  if ( vec == NULL ) {
    fprintf (stderr, "Memory Allocation, Failed, xx_vector*\n");
    return NULL;
  }

  if ( item_size <= 0 ) {
    fprintf (stderr, "Invaid, Item Size cannot be less or equal to '0'\n");
  } else {
    vec -> item_size = item_size;
  }

  vec -> cursor = 0;
  vec -> capacity = XX_VECTOR_DEFAULT_CAPACITY;

  // allocating memory to data
  vec -> data = malloc ( vec -> item_size * vec -> capacity );
  if ( vec -> data == NULL ) {
    fprintf (stderr, "Memory Allocation, Failed, xx_vector* -> void*\n");
    return NULL;
  }


  return vec;
}

void xx_add_to_vector ( xx_vector* vec, void* l_data ) {
  // checking for the overflow
  if ( vec -> cursor == vec -> capacity ) {
    int extend_size = vec -> capacity * 2;
    vec -> capacity = extend_size;
    void* ptr = realloc ( vec -> data, (vec -> item_size * extend_size ));
    if ( ptr == NULL ) {
      fprintf (stderr, "xx_add_to_vector() - failed, memory allocation\n");
      return;
    } else {
      vec -> data = ptr;
    }
  }

  memcpy ( ( (char*) (vec -> data) + (vec -> item_size * vec -> cursor)), l_data, vec -> item_size );
  vec -> cursor += 1;
}

void* xx_read_from_vector (xx_vector* vec, int cur) {
  if ( cur >= vec -> cursor ) {
    fprintf (stdout, "Warning! This value exceeds or equals the current cursor, returning the latest value\n");
    cur = vec -> cursor - 1;
  } else if ( cur < 0 ) {
    fprintf (stdout, "Warning! Cursor Value exceeds negaive '0', returning the value at '0'\n");
  }

  // memcpy ( vec -> return_data, (vec -> data + ( vec -> item_size * cur )), vec -> item_size );
  return (char*) (vec -> data) + (vec -> item_size * cur);
}

void xx_free_vector ( xx_vector* vec ) {
  if ( vec -> data != NULL ) {
    free ( vec -> data );
    vec -> data = NULL;
  }

  if ( vec != NULL ) {
    free ( vec );
    vec = NULL;
  }
}
