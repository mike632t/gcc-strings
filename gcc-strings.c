/*
 * gcc-strings.c
 * 
 * Copyright(C)2024  MT
 *
 * String manipulation in C.
 * 
 * Concatenate
 * Copy
 * Shuffle (in place)
 * Reverse (in place)
 * Upper (in place)
 * Lower (in place)
 * Sort (in place)
 * 
 * Append
 * Compare
 * Position
 * Is empty
 *
 * 'cc strings'
 * 'link strings,sys$library:vaxcrtl.olb/lib'
 *
 * This  program is free software: you can redistribute it and/or modify it
 * under  the terms of the GNU General Public License as published  by  the
 * Free  Software Foundation, either version 3 of the License, or (at  your
 * option) any later version.
 *
 * This  program  is distributed in the hope that it will  be  useful,  but
 * WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You  should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * https://rosettacode.org/wiki/Knuth_shuffle
 * 
 * https://stackoverflow.com/questions/33294426
 * https://stackoverflow.com/questions/784417/
 *
 * 10 Nov 24   0.1   - Initial version - MT 
 *
 */

#define NAME           "gcc-strings"
#define VERSION        "0.1"
#define BUILD          "0001"
#define DATE           "10 Nov 24"
#define AUTHOR         "MT"

#if defined (DEBUG)
#define debug(code) do {fprintf(stderr, "Debug\t: %s line : %d : ", \
            __FILE__, __LINE__); code;} while(0)
#else
#define debug (code)
#endif

#include <stdio.h>   /* printf() */
#include <string.h>  /* strcpy(), strcat() */
#include <stdlib.h>  /* malloc() */
#include <stdarg.h> 
#include <time.h>    /* time() */
#include <ctype.h>   /* toupper() */

#define CONSONANTS  "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
#define VOWELS      "aeiouAEIOU"
#define PUNCTUATION ".,:;!?" 

void v_error (const char *s_format, ...) /* Print formatted error message and exit */
{
   va_list t_args;
   va_start (t_args, s_format);
   fprintf (stderr, "%s : ", __FILE__);
   vfprintf (stderr, s_format, t_args);
   va_end (t_args);
   exit (-1);
}

char* concat (const char* _first, const char* _second) /* Concatenate two strings */
{
   char* _output = malloc(strlen(_first) + strlen(_second) + 1);
   strcpy(_output, _first);
   strcat(_output, _second);
   return _output;
}

char* copy (const char* s_string) /* Copy a string */
{
   char* s_output = malloc(strlen(s_string) + 1);
   char* s_pointer = s_output;
   while (*s_string)
   {
       *s_output++ = *s_string++;
   }
   *s_output = '\0';
   return s_pointer;
}
/*
{
   int i_length = strlen(s_string) + 1;
   char* s_output = malloc(i_length);
   memcpy(s_output, s_string, i_length);
   return s_output;
}
*/

void shuffle_i(char* s_string)
/* 
 * Knuth Shuffle
 * 
 * for i from last downto 1 do:
 *    let j = random integer in range 0 
 *    swap items[i] with items[j]
 */
{
   int i_length = strlen(s_string) - 1;
   int i_offset;
   int i_count;
   
   for(i_count = i_length; i_count > 1 ; i_count--)
   {
      i_offset = (int)((double)i_count * (rand() / (RAND_MAX + 1.0)));
      s_string[i_count] ^= s_string[i_offset]; s_string[i_offset] ^= s_string[i_count]; s_string[i_count] ^= s_string[i_offset]; /* swap */
   }
}

void reverse_i (char* s_string) /* Reverse a string (in place, modifying the original string) */
{
   char *p_start = s_string;
   char *p_end = p_start + strlen(s_string) - 1; /* -1 for \0 */
   char c_temp;

   while (p_start < p_end) /* Pointer arithmetic */
   {
      c_temp = *p_start;
      *p_start++ = *p_end;
      *p_end-- = c_temp;
   }
}

void upper_i (char* s_string) /* Convert string to uppercase (in place, modifying the original string) */
{
   while (*s_string)
   {
      if (islower(*s_string)) *s_string = toupper(*s_string);
      s_string++;
   }
}

void lower_i (char *s_string)
{
   while (*s_string)
   {
      if (isupper(*s_string)) *s_string = tolower(*s_string);
      s_string++;
   }
}

int compare(const void* c_first, const void* c_second)
{
    if (*(char*) c_first != *(char*) c_second) /* Compare characters */
        return *(char *) c_first - *(char *) c_second; 
    return 0;
}

void sort_i (char* s_string) /* Sort string) */
{
   qsort (s_string, strlen(s_string), sizeof *s_string, compare); /* Sort alphabetic characters in place */
}


int main()
{
   char* s_alphabet = concat(CONSONANTS, VOWELS);
   char* s_consonants = CONSONANTS;
   char* s_vowels  = VOWELS;
   char* s_punctuation = PUNCTUATION;
   char* s_all;
   char* s_letters;
   char* s_null = "";
   
   /** srand((unsigned)(time(NULL))); /* Seed random number generator with an unsigned value. */

   /* Note - Some older versions of C do not allow negative field widths so
    * a variable number of spaces are used instead. */
   
   printf ("%*s = %s%*s(%ld)\n", 23, "CONSONANTS", s_consonants, (int)(63 - strlen(s_consonants)), " ",strlen(s_consonants));
   printf ("%*s = %s%*s(%ld)\n", 23, "VOWELS", s_vowels, (int)(63 - strlen(s_vowels)), " ", strlen(s_vowels));
   shuffle_i (s_alphabet);
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (shuffled)", s_alphabet, (int)(63 - strlen(s_alphabet)), " ", strlen(s_alphabet));
   sort_i (s_alphabet); /* Sort alphabetic characters in place */
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (sorted)", s_alphabet, (int)(63 - strlen(s_alphabet)), " ", strlen(s_alphabet));
   s_letters = copy(s_alphabet);
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (copy)", s_letters, (int)(63 - strlen(s_letters)), " ", strlen(s_letters));
   reverse_i(s_alphabet); /* Reverse the order */
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (reversed)", s_alphabet, (int)(63 - strlen(s_alphabet)), " ", strlen(s_alphabet));
   printf ("%*s = %s%*s(%ld)\n", 23, "PUNCTUATION", s_punctuation, (int)(63 - strlen(s_punctuation)), " ", strlen(s_punctuation));
   reverse_i(s_alphabet); /* Reverse it back again */
   s_all = concat(s_alphabet, s_null);
   s_all = concat(s_alphabet, s_punctuation); 
   printf ("%*s = %s%*s(%ld)\n", 23, "EVERYTHING", s_all, (int)(63 - strlen(s_all)), " ", strlen(s_all));
   free (s_all);
   upper_i (s_alphabet);
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (uppercase)", s_alphabet, (int)(63 - strlen(s_alphabet)), " ", strlen(s_alphabet));
   lower_i (s_alphabet);
   printf ("%*s = %s%*s(%ld)\n", 23, "ALPHABET (lowercase)", s_alphabet, (int)(63 - strlen(s_alphabet)), " ", strlen(s_alphabet));
}
