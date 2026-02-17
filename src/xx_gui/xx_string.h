/* 
 *  function - declarations
 *  */
int xx_strlen (char* i_string); // just returns string length
void xx_strcpy (char* dest_string, char* src_string); // just copies to the destination string from source string                                
void xx_strcat (char* source_string, char* destination_string); // just concatines to the source string from the destination 
int xx_abs (int value); // just returns the positive value, whether input is positive / negative
void xx_strcat_ch (char* source, char* ch); // just concatinates a character to the source string 
void xx_trim_n (char* source, char* destination, int from, int size); // trims a src string from - size to the destination string 
void xx_slice (char* source, char* destination, char from, char to); // cuts out a substring (destinatino) from the source, from character to 
                                                                     // another character "if* one = this;"
                                                                     // xx_slice ("if* one = this;", buffer, '*', '=');
void xx_pop_back (char* source); // just removes the last elements from the source string 
void xx_push_back (char* source, char i); // adds a character to the end of the source - make sure to have enough source string buffer
int xx_strcmpi (char* string1, char* string2); // compares two strings and returns the difference

void xx_shift (char* i_string); // removes the first elements
void xx_unshift (char* i_string, char ch); // adds to the first character / index

int xx_strstr (char* big_string, char* search); // search the search string in side of the big string


int xx_strcpy_string (char* main_string, char* inputting_string, int ind); // appends the string to a single 1d array of char (string)

/* 
 *  extra function - declarations
 * */
int xx_get_index (char* source, char ch);




/* 
  just strlen function but no need to include string.h
*/
int xx_strlen (char* i_string) {
  int counter = 0;
  
  while (i_string[counter] != '\0') {
    counter ++;
  }
  
  
  return counter;
}

/* 
  just strcpy function but no need to include string.h
*/
void xx_strcpy (char* dest_string, char* src_string) {
  
  int i = 0;
  while (src_string [i] != '\0') {
    dest_string[i] = src_string[i];
    i++;
  }
  
  dest_string [i] = '\0';
  
}

/* 
  just abs function but no need to include math.h 
*/
int xx_abs (int value) {
  if (value > 0) {
    return value;
  }
  return (-1) * value;
}

/* 
  just strcat function but no need to include string.h
*/
void xx_strcat (char* source, char* destination) {
  // getting the string length of the destination and source
  int dest_size = xx_strlen (destination);
  int src_size = xx_strlen (source);
  
  printf ("Dest_size : %d\n", dest_size);
  
  int i = 0;
  
  for (i = 0; i < dest_size; i++) {
    source[src_size] = destination[i];
    // destination[]
    src_size ++;
  }
  
  source[src_size] = '\0';
}


// this one just concatinates one character 
void xx_strcat_ch (char* source, char* ch) {
  
  int src_size = xx_strlen (source);
  
  source [src_size] = *ch;
  
  source [src_size + 1] = '\0';
  
  
  
}


/* 
  function - char* xx_slice (char* source, int from, int to)
      - cuts out the source string from - to
      - returns the (sliced) string
*/
/* char* xx_slice (char* source, int from, int to) {
  size_t string_size = xx_strlen (source);
  size_t r = to - from;
  
  char* r_string = (char*) calloc (r, sizeof(char));
  
  if (to < from) {
    printf ("\t ! 'to' argument is greater than 'from'\n");
    return NULL;
  }
  
  // for (int i = 0; i < r; i++) {
    // r_string = 
  // }
  
  
  return r_string;
} */

/* 
  function - xx_trim_n (char* source, char* destination, int from, int size)
*/
void xx_trim_n (char* source, char* destination, int from, int size) {
  
  for (int i = 0; i < size; i++) {
    destination [i] = source[from + i];
  }
  
  destination [size] = '\0';
  
}

/* 
  function - xx_pop_back (char* source)
    -- removes the last element
*/
void xx_pop_back (char* source) {
  source [xx_strlen(source) - 1] = '\0';
}

/* 
  function - xx_push_back (char* source)
    -- adds to the last 
*/
void xx_push_back (char* source, char i) {
  int o = xx_strlen (source);
  source [o] = i;
  source [o + 1] = '\0';
  
}


/*
 * this is just string compare function
 * will return 0 if the strings are common
 * */
int xx_strcmpi (char* string1, char* string2) {
  int diff = 0;

  int string_size1 = xx_strlen (string1);
  int string_size2 = xx_strlen (string2);

  if (string_size1 != string_size2) {
    diff = xx_abs (string_size1 - string_size2);
    return diff;
  }


  for (int i = 0; string1[i] != '\0'; i++) {
    if (string1[i] != string2[i]) {
      diff ++;
    }
  }
  return diff;
}

/* 
 * function to return the index of a character from the source file
 * */
int xx_get_index (char* source, char ch) {
  int return_value = -1;
  // getting the source length
  int string_size = xx_strlen (source);

  // looping through the main string 
  // and break the loop as soon as you find the first occurance of that character
  for (int i = 0; i < string_size; i++) {
    if (source [i] == ch) {
      return_value = i;
      break;
    }
  }


  return return_value;
}

/* 
 * function - void xx_slice (char* source, char* destination, char from, char to); 
 *  -- this function will get you the slice of the source string from that character to another character (first occurance)
 *  */
void xx_slice (char* source, char* destination, char from, char to) {

  int i_from = xx_get_index (source, from) + 1;
  int i_to = xx_get_index (source, to);

  int j = 0;
  for (int i = i_from; i < i_to; i++) {

    destination [j] = source [i];
    j++;
  }

  destination [j] = '\0';
}

/* 
 * function - void xx_shift (char* i_string)
 *  -- removes first elements from the string 
 * */
void xx_shift (char* i_string) {
  int string_size = xx_strlen (i_string);


  int j = 1;
  for (int i = 0; i < string_size; i++) {
    i_string[i] = i_string [j];
    j++;
  }
}

/* 
 * function - void xx_unshift (char* i_string, char ch); 
 *     -- adds to the front from the string 
 *     -- remember to have enough buffer space for the string
 *
 * * */
void xx_unshift (char* i_string, char ch) {
  int string_size = xx_strlen (i_string);

  for (int i = string_size; i > 0; i--) {
    i_string [i] = i_string[i - 1];
  }

  i_string [0] = ch;
  i_string [string_size + 1] = '\0';
}

/* 
 * function - 
int xx_strstr (char* big_string, char* search); // search the search string in side of the big string
  -- checks if the inputted string is inside of the main string 
  -- returns 1 or the index of the string
 * */
int xx_strstr (char* big_string, char* search) {
  int r_value = -1;


  int b_string_size = xx_strlen (big_string); // string length for the main string / source string
  int s_string_size = xx_strlen (search); // string length for the string

  int a = xx_get_index (big_string, search[0]);
  if (a == -1) {
    r_value = -1; // meaning we could not find anything
    return r_value; 
  } 

  /* 
   * making a working formula  
   * */
  int l_j = 0;
  for (int i = 0; i < b_string_size; i++) {

    if (search[0] == big_string[i]) {
      // if the very first letters match then we start to match other letters
      for (int j = i; l_j < s_string_size ; j++) {
        // if there is a mistake
        if (search[l_j] != big_string [j]) {
          l_j = 0;
          break;
        }
        l_j ++;
      }
      if (l_j >= s_string_size) {
        r_value = i;
        break;
      }
    }
  }

  return r_value;
}

// function xx_strcpy_string
// returns 0 on failure, and 1 on success
// this function will store the string from that particular index,
// it is very useful when you only allocate a single or 1d array for string,
int xx_strcpy_string (char* main_string, char* inputting_string, int ind){
  int r_value = 1;

  int l_ind = ind;
  int string_length = xx_strlen (inputting_string);
  for (int i = 0; i < string_length; i++) {
    main_string [l_ind] = inputting_string [i];
    l_ind++;
  }

  return 1;
}
