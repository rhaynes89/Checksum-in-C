/*
Name: Richard Haynes III
Assignment: Security in Computing Checksum
Date: 4/4/2020
 */

/*
  1. First parameter is the name of the file. Second is the
  size in bits of the checksum.
  2. If 8, 16, 32 are not entered for the checksum the user
  should see this: "Valid checksum sizes are 8, 16, or 32". The
  message should be sent to STDERR.
  3. Output the input file (80 characters per row). Print the checksum.
  4. The checksum line: X bit checksum is Y for all ZZZ characters
    - %2d bit checksum is %8lx for all %4 chars\n,
      checkSumSize, checksum, characterCount
  5. X: checksum size, 8, 16, 32
    - Y: calculated checkSumSize
    - ZZZ: character count of input file.
  6. Pad the input file with X if short on characters.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 80

unsigned int power(int x, int y)
{
    if(y == 0)
    {
        return 1;
    }
    return x * power(x, --y);
}

int main(int argc, char **argv)
{
  int i = 0, j = 0;
  int count = 0;
  int checkSumSize = atoi(argv[2]), characterCount = 0;
  unsigned int checksum = 0;
  char text[500];

  char *fname = argv[1];
  FILE *file = fopen(fname, "r");
  if(file == NULL)
  {
    //printf("File doesn't exist.\n");
    exit(1);
  }
  else
  {
    //printf("File opened successfully.\n");
  }

    printf("\n");
  do{
      char characters = fgetc(file);
      if(feof(file))
      {
          break;
      }
      text[i] = characters;
      printf("%c", characters);
      i++;
      if(i % SIZE == 0)
      {
        printf("\n");
      }
  }while(1);
  characterCount = i - 1;
  //used to check character count.
  //printf("%d character count\n\n", characterCount);

  if(checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32)
  {
    fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
    exit(1);
  }

  if(checkSumSize == 8)
  {
      /*
          A = 65
          65 = 01000001
          (A+A)+ A) + A) ...
          intput text: a = 97
          0110 0001 = in hex: 61

          input text: AAAAAAAA
          01000001 + 01000001 + 01000001 + 01000001 + 01000001 +
          01000001 + 01000001 + 01000001 + 01000001 + 01000001 =
          94

           01000001 current value
          +01000001 temp

           10000010 new value
          +01000001
      */
    int temp[8] = {0,0,0,0,0,0,0,0};
    int count = 0, carry = 0;
    while(count < characterCount)
    {
	  int value[8] = {0,0,0,0,0,0,0,0};
      carry = 0;
      j = 7;
      int val = text[count];
      while(val > 0)
      {
        value[j] = val % 2;
        val /= 2;
        j--;
      }
      //line below was used to see binary values
      //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

      for(i = 7; i >= 0; i--)
      {
        // both arrays have 0 and carry is 0 == 0
        if(value[i] == 0 && temp[i] == 0 && carry == 0)
        {
            temp[i] = 0;
            carry = 0;
        }
        // one array has 1 and carry is 0 == 1
        else if(value[i] == 1 && temp[i] == 0 && carry == 0)
        {
            temp[i] = 1;
            carry = 0;
        }
        else if(value[i] == 0 && temp[i] == 1 && carry == 0)
        {
            temp[i] = 1;
            carry = 0;
        }
        // both arrays have 1 and carry is 0 == 0
        else if(value[i] == 1 && temp[i] == 1 && carry == 0)
        {
            temp[i] = 0;
            carry = 1;
        }
        // both arrays have 0 and carry is 1 == 1
        else if(value[i] == 0 && temp[i] == 0 && carry == 1)
        {
            temp[i] = 1;
            carry = 0;
        }
        // one array has 1 and carry is 1 == 0
        else if(value[i] == 1 && temp[i] == 0 && carry == 1)
        {
            temp[i] = 0;
            carry = 1;
        }
        else if(value[i] == 0 && temp[i] == 1 && carry == 1)
        {
            temp[i] = 0;
            carry = 1;
        }
        // both arrays have 1 and carry is 1 == 1
        else if(value[i] == 1 && temp[i] == 1 && carry == 1)
        {
            temp[i] = 1;
            carry = 1;
        }
      }
	  //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);
      count++;
    }
    //used to check binary number
    //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

    int newLine[8] = {0,0,0,0,1,0,1,0};
    carry = 0;
    for(i = 7; i >= 0; i--)
    {
      // both arrays have 0 and carry is 0 == 0
      if(newLine[i] == 0 && temp[i] == 0 && carry == 0)
      {
			temp[i] = 0;
			carry = 0;
      }
      // one array has 1 and carry is 0 == 1
      else if(newLine[i] == 1 && temp[i] == 0 && carry == 0)
      {
			temp[i] = 1;
			carry = 0;
      }
      else if(newLine[i] == 0 && temp[i] == 1 && carry == 0)
      {
			temp[i] = 1;
			carry = 0;
      }
      // both arrays have 1 and carry is 0 == 0
      else if(newLine[i] == 1 && temp[i] == 1 && carry == 0)
      {
			temp[i] = 0;
			carry = 1;
      }
      // both arrays have 0 and carry is 1 == 1
      else if(newLine[i] == 0 && temp[i] == 0 && carry == 1)
      {
			temp[i] = 1;
			carry = 0;
      }
      // one array has 1 and carry is 1 == 0
      else if(newLine[i] == 1 && temp[i] == 0 && carry == 1)
      {
			temp[i] = 0;
			carry = 1;
      }
      else if(newLine[i] == 0 && temp[i] == 1 && carry == 1)
      {
			temp[i] = 0;
			carry = 1;
      }
      // both arrays have 1 and carry is 1 == 1
      else if(newLine[i] == 1 && temp[i] == 1 && carry == 1)
      {
			temp[i] = 1;
			carry = 1;
      }
    }

    int y = 0;
    for(i = 7; i >= 0; i--)
	{
        checksum += temp[i] * power(2, y);
        y++;
    }
    printf("\n");
    printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+1);
    printf("\n");
  }
  else if(checkSumSize == 16)
  {
    /*
        mod characterCount by 2. if == 0 then no padding
        else add remainder X's.

        TEXT: AB

        A = 01000001
        B = 01000010
        01000001 01000010

        TEXT: A
        A = 01000001
        X = 01011110
        01000001 01011110

    */

    int temp[16] = {0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0};
    int count = 0, carry = 0, flag = 0;

    if((characterCount + 1) % 2 == 1)
    {
      flag = 1; // odd number of characters
    }
    else
    {
      flag = 0; // even number of characters
    }
    if(flag == 0)
    {
        while(count < characterCount - 1) // This is to hardcode 2nd to last character and newline character
        {
		  int value[16] = {0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0};
          carry = 0;
          j = 7;
          int val = text[count];
          while(val > 0)
          {
            value[j] = val % 2;
            val /= 2;
            j--;
          }
          count++;
          val = text[count];
          j = 15;
          while(val > 0)
          {
            value[j] = val % 2;
            val /= 2;
            j--;
          }
          //line below was used to see binary values
          //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

          /*
                ABCD
                0123

                value1 = 01000001
                value2 = 01000010
                As 16-bits: 01000001 01000010
                temp1 = 01000011
                temp2 = 01000100
                As 16-bits: 01000011 01000100

                value1 + temp1 = 01000001 + 01000011 = 10000100
                value2 + temp2 = 01000010 + 01000100 = 10000110
                As 16-bits 10000100 10000110 = finalValue
          */

          for(i = 15; i >= 0; i--)
          {
            // both arrays have 0 and carry is 0 == 0
            if(value[i] == 0 && temp[i] == 0 && carry == 0)
            {
                 temp[i] = 0;
                 carry = 0;
            }
            // one array has 1 and carry is 0 == 1
            else if(value[i] == 1 && temp[i] == 0 && carry == 0)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            else if(value[i] == 0 && temp[i] == 1 && carry == 0)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            // both arrays have 1 and carry is 0 == 0
            else if(value[i] == 1 && temp[i] == 1 && carry == 0)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            // both arrays have 0 and carry is 1 == 1
            else if(value[i] == 0 && temp[i] == 0 && carry == 1)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            // one array has 1 and carry is 1 == 0
            else if(value[i] == 1 && temp[i] == 0 && carry == 1)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            else if(value[i] == 0 && temp[i] == 1 && carry == 1)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            // both arrays have 1 and carry is 1 == 1
            else if(value[i] == 1 && temp[i] == 1 && carry == 1)
            {
                temp[i] = 1;
                carry = 1;
            }
          }
          count++;
        }

        // Get second to last character store in value
		int value[16] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0};
        j = 7;
        int val = text[count];
        while(val > 0)
        {
          value[j] = val % 2;
          val /= 2;
          j--;
        }
		
        carry = 0;
        for(i = 15; i >= 0; i--)
        {
            // both arrays have 0 and carry is 0 == 0
            if(value[i] == 0 && temp[i] == 0 && carry == 0)
            {
                temp[i] = 0;
                carry = 0;
            }
          // one array has 1 and carry is 0 == 1
           else if(value[i] == 1 && temp[i] == 0 && carry == 0)
           {
                temp[i] = 1;
                carry = 0;
           }
          else if(value[i] == 0 && temp[i] == 1 && carry == 0)
          {
               temp[i] = 1;
               carry = 0;
          }
          // both arrays have 1 and carry is 0 == 0
          else if(value[i] == 1 && temp[i] == 1 && carry == 0)
          {
               temp[i] = 0;
               carry = 1;
          }
          // both arrays have 0 and carry is 1 == 1
          else if(value[i] == 0 && temp[i] == 0 && carry == 1)
          {
               temp[i] = 1;
               carry = 0;
          }
          // one array has 1 and carry is 1 == 0
          else if(value[i] == 1 && temp[i] == 0 && carry == 1)
          {
               temp[i] = 0;
               carry = 1;
          }
          else if(value[i] == 0 && temp[i] == 1 && carry == 1)
          {
               temp[i] = 0;
               carry = 1;
          }
          // both arrays have 1 and carry is 1 == 1
          else if(value[i] == 1 && temp[i] == 1 && carry == 1)
          {
              temp[i] = 1;
              carry = 1;
          }
        }
    }
    else // this means the characterCount is odd
    {
        while(count < characterCount) // This is to hardcode 2nd to last character and newline character
        {
		  int value[16] = {0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0};
          carry = 0;
          j = 7;
          int val = text[count];
          while(val > 0)
          {
            value[j] = val % 2;
            val /= 2;
            j--;
          }
          count++;
          val = text[count];
          j = 15;
          while(val > 0)
          {
            value[j] = val % 2;
            val /= 2;
            j--;
          }

          for(i = 15; i >= 0; i--)
          {
            // both arrays have 0 and carry is 0 == 0
            if(value[i] == 0 && temp[i] == 0 && carry == 0)
            {
                 temp[i] = 0;
                 carry = 0;
            }
            // one array has 1 and carry is 0 == 1
            else if(value[i] == 1 && temp[i] == 0 && carry == 0)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            else if(value[i] == 0 && temp[i] == 1 && carry == 0)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            // both arrays have 1 and carry is 0 == 0
            else if(value[i] == 1 && temp[i] == 1 && carry == 0)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            // both arrays have 0 and carry is 1 == 1
            else if(value[i] == 0 && temp[i] == 0 && carry == 1)
            {
                 temp[i] = 1;
                 carry = 0;
            }
            // one array has 1 and carry is 1 == 0
            else if(value[i] == 1 && temp[i] == 0 && carry == 1)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            else if(value[i] == 0 && temp[i] == 1 && carry == 1)
            {
                 temp[i] = 0;
                 carry = 1;
            }
            // both arrays have 1 and carry is 1 == 1
            else if(value[i] == 1 && temp[i] == 1 && carry == 1)
            {
                temp[i] = 1;
                carry = 1;
            }
          }
          count++;
        }

        int newLine[16] = {0,0,0,0,1,0,1,0,0,1,0,1,1,0,0,0};
        carry = 0;
        for(i = 15; i >= 0; i--)
        {
          // both arrays have 0 and carry is 0 == 0
          if(newLine[i] == 0 && temp[i] == 0 && carry == 0)
          {
              temp[i] = 0;
              carry = 0;
          }
          // one array has 1 and carry is 0 == 1
          else if(newLine[i] == 1 && temp[i] == 0 && carry == 0)
          {
              temp[i] = 1;
              carry = 0;
          }
          else if(newLine[i] == 0 && temp[i] == 1 && carry == 0)
          {
               temp[i] = 1;
               carry = 0;
          }
          // both arrays have 1 and carry is 0 == 0
          else if(newLine[i] == 1 && temp[i] == 1 && carry == 0)
          {
               temp[i] = 0;
               carry = 1;
          }
          // both arrays have 0 and carry is 1 == 1
          else if(newLine[i] == 0 && temp[i] == 0 && carry == 1)
          {
               temp[i] = 1;
               carry = 0;
          }
          // one array has 1 and carry is 1 == 0
          else if(newLine[i] == 1 && temp[i] == 0 && carry == 1)
          {
               temp[i] = 0;
               carry = 1;
          }
          else if(newLine[i] == 0 && temp[i] == 1 && carry == 1)
          {
               temp[i] = 0;
               carry = 1;
          }
          // both arrays have 1 and carry is 1 == 1
          else if(newLine[i] == 1 && temp[i] == 1 && carry == 1)
          {
              temp[i] = 1;
              carry = 1;
          }
        }
    }
    //used to check binary number
    //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

    int y = 0;
    for(i = 15; i >= 0; i--)
    {
        checksum += temp[i] * power(2, y);
        y++;
    }

    if(flag == 1)
    {
        printf("X\n");
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+2);
    }
	else
	{
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+1);
	}
    printf("\n");
  }
  else if(checkSumSize == 32)
  {
	int temp[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int count = 0, carry = 0, flag = 4 - ((characterCount + 1) % 4);
	if(flag == 4) // Need to add 0 X's
	{
		while(count < characterCount - 3) // This is to hardcode 2nd to last character and newline character
		{
		  int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		  carry = 0;
		  j = 7;
		  int val = text[count];
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 15;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 23;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 31;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  //line below was used to see binary values
		  //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

		  for(i = 31; i >= 0; i--)
		  {
			// both arrays have 0 and carry is 0 == 0
			if(value[i] == 0 && temp[i] == 0 && carry == 0)
			{
				 temp[i] = 0;
				 carry = 0;
			}
			// one array has 1 and carry is 0 == 1
			else if(value[i] == 1 && temp[i] == 0 && carry == 0)
			{
				 temp[i] = 1;
				 carry = 0;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 0)
			{
				 temp[i] = 1;
				 carry = 0;
			}
			// both arrays have 1 and carry is 0 == 0
			else if(value[i] == 1 && temp[i] == 1 && carry == 0)
			{
				 temp[i] = 0;
				 carry = 1;
			}
			// both arrays have 0 and carry is 1 == 1
			else if(value[i] == 0 && temp[i] == 0 && carry == 1)
			{
				 temp[i] = 1;
				 carry = 0;
			}
			// one array has 1 and carry is 1 == 0
			else if(value[i] == 1 && temp[i] == 0 && carry == 1)
			{
				 temp[i] = 0;
				 carry = 1;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 1)
			{
				 temp[i] = 0;
				 carry = 1;
			}
			// both arrays have 1 and carry is 1 == 1
			else if(value[i] == 1 && temp[i] == 1 && carry == 1)
			{
				temp[i] = 1;
				carry = 1;
			}
		  }
		  count++;
		}

		// Get second to last character store in value
		int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0};
		j = 7;
		int val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		count++;
		j = 15;
		val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		count++;
		j = 23;
		val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		
		carry = 0;
		for(i = 31; i >= 0; i--)
		{
		  // both arrays have 0 and carry is 0 == 0
		  if(value[i] == 0 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 0;
			carry = 0;
		  }
		  // one array has 1 and carry is 0 == 1
		  else if(value[i] == 1 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // both arrays have 1 and carry is 0 == 0
		  else if(value[i] == 1 && temp[i] == 1 && carry == 0)
		  {
			   temp[i] = 0;
			   carry = 1;
		  }
		  // both arrays have 0 and carry is 1 == 1
		  else if(value[i] == 0 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // one array has 1 and carry is 1 == 0
		  else if(value[i] == 1 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 1 and carry is 1 == 1
		  else if(value[i] == 1 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 1;
			carry = 1;
		  }
		}
	}
	else if(flag == 1) // Need to add 1 X's
	{
		while(count < characterCount - 2) // This is to hardcode 2nd to last character and newline character
		{
		  int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		  carry = 0;
		  j = 7;
		  int val = text[count];
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 15;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 23;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 31;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  //line below was used to see binary values
		  //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

		  for(i = 31; i >= 0; i--)
		  {
			// both arrays have 0 and carry is 0 == 0
			if(value[i] == 0 && temp[i] == 0 && carry == 0)
			{
			 temp[i] = 0;
			 carry = 0;
			}
			// one array has 1 and carry is 0 == 1
			else if(value[i] == 1 && temp[i] == 0 && carry == 0)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 0)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			// both arrays have 1 and carry is 0 == 0
			else if(value[i] == 1 && temp[i] == 1 && carry == 0)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			// both arrays have 0 and carry is 1 == 1
			else if(value[i] == 0 && temp[i] == 0 && carry == 1)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			// one array has 1 and carry is 1 == 0
			else if(value[i] == 1 && temp[i] == 0 && carry == 1)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 1)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			// both arrays have 1 and carry is 1 == 1
			else if(value[i] == 1 && temp[i] == 1 && carry == 1)
			{
			 temp[i] = 1;
			 carry = 1;
			}
		  }
		  //printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15],temp[16],temp[17],temp[18],temp[19],temp[20],temp[21],temp[22],temp[23],temp[24],temp[25],temp[26],temp[27],temp[28],temp[29],temp[30],temp[31]);

		  count++;
		}

		// Get second to last character store in value
		int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,0,0,0};
		j = 7;
		int val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		count++;
		j = 15;
		val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		
		carry = 0;
		for(i = 31; i >= 0; i--)
		{
		  // both arrays have 0 and carry is 0 == 0
		  if(value[i] == 0 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 0;
			carry = 0;
		  }
		  // one array has 1 and carry is 0 == 1
		  else if(value[i] == 1 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // both arrays have 1 and carry is 0 == 0
		  else if(value[i] == 1 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 0 and carry is 1 == 1
		  else if(value[i] == 0 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // one array has 1 and carry is 1 == 0
		  else if(value[i] == 1 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 1 and carry is 1 == 1
		  else if(value[i] == 1 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 1;
			carry = 1;
		  }
		}
		//printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9],temp[10],temp[11],temp[12],temp[13],temp[14],temp[15],temp[16],temp[17],temp[18],temp[19],temp[20],temp[21],temp[22],temp[23],temp[24],temp[25],temp[26],temp[27],temp[28],temp[29],temp[30],temp[31]);

	}
	else if(flag == 2) // Need to add 2 X's
	{
		while(count < characterCount - 1) // This is to hardcode 2nd to last character and newline character
		{
		  int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		  carry = 0;
		  j = 7;
		  int val = text[count];
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 15;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 23;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 31;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  //line below was used to see binary values
		  //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

		  for(i = 31; i >= 0; i--)
		  {
			// both arrays have 0 and carry is 0 == 0
			if(value[i] == 0 && temp[i] == 0 && carry == 0)
			{
				temp[i] = 0;
				carry = 0;
			}
			// one array has 1 and carry is 0 == 1
			else if(value[i] == 1 && temp[i] == 0 && carry == 0)
			{
				temp[i] = 1;
				carry = 0;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 0)
			{
				temp[i] = 1;
				carry = 0;
			}
			// both arrays have 1 and carry is 0 == 0
			else if(value[i] == 1 && temp[i] == 1 && carry == 0)
			{
				temp[i] = 0;
				carry = 1;
			}
			// both arrays have 0 and carry is 1 == 1
			else if(value[i] == 0 && temp[i] == 0 && carry == 1)
			{
				temp[i] = 1;
				carry = 0;
			}
			// one array has 1 and carry is 1 == 0
			else if(value[i] == 1 && temp[i] == 0 && carry == 1)
			{
				temp[i] = 0;
				carry = 1;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 1)
			{
				temp[i] = 0;
				carry = 1;
			}
			// both arrays have 1 and carry is 1 == 1
			else if(value[i] == 1 && temp[i] == 1 && carry == 1)
			{
				temp[i] = 1;
				carry = 1;
			}
		  }
		  count++;
		}

		// Get second to last character store in value
		int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0};
		j = 7;
		int val = text[count];
		while(val > 0)
		{
		  value[j] = val % 2;
		  val /= 2;
		  j--;
		}
		
		carry = 0;
		for(i = 31; i >= 0; i--)
		{
		  // both arrays have 0 and carry is 0 == 0
		  if(value[i] == 0 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 0;
			carry = 0;
		  }
		  // one array has 1 and carry is 0 == 1
		  else if(value[i] == 1 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // both arrays have 1 and carry is 0 == 0
		  else if(value[i] == 1 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 0 and carry is 1 == 1
		  else if(value[i] == 0 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // one array has 1 and carry is 1 == 0
		  else if(value[i] == 1 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 1 and carry is 1 == 1
		  else if(value[i] == 1 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 1;
			carry = 1;
		  }
		}
	}
	else if(flag == 3) // Need to add 3 X's
	{
		while(count < characterCount) // This is to hardcode 2nd to last character and newline character
		{
		  int value[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		  carry = 0;
		  j = 7;
		  int val = text[count];
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 15;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 23;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  count++;
		  val = text[count];
		  j = 31;
		  while(val > 0)
		  {
			value[j] = val % 2;
			val /= 2;
			j--;
		  }
		  //line below was used to see binary values
		  //printf("%d, %d, %d, %d, %d, %d, %d, %d\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);

		  for(i = 31; i >= 0; i--)
		  {
			// both arrays have 0 and carry is 0 == 0
			if(value[i] == 0 && temp[i] == 0 && carry == 0)
			{
			 temp[i] = 0;
			 carry = 0;
			}
			// one array has 1 and carry is 0 == 1
			else if(value[i] == 1 && temp[i] == 0 && carry == 0)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 0)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			// both arrays have 1 and carry is 0 == 0
			else if(value[i] == 1 && temp[i] == 1 && carry == 0)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			// both arrays have 0 and carry is 1 == 1
			else if(value[i] == 0 && temp[i] == 0 && carry == 1)
			{
			 temp[i] = 1;
			 carry = 0;
			}
			// one array has 1 and carry is 1 == 0
			else if(value[i] == 1 && temp[i] == 0 && carry == 1)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			else if(value[i] == 0 && temp[i] == 1 && carry == 1)
			{
			 temp[i] = 0;
			 carry = 1;
			}
			// both arrays have 1 and carry is 1 == 1
			else if(value[i] == 1 && temp[i] == 1 && carry == 1)
			{
			 temp[i] = 1;
			 carry = 1;
			}
		  }
		  count++;
		}

		// Get second to last character store in value
		int value[32] = {0,0,0,0,1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0};
		
		carry = 0;
		for(i = 31; i >= 0; i--)
		{
		  // both arrays have 0 and carry is 0 == 0
		  if(value[i] == 0 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 0;
			carry = 0;
		  }
		  // one array has 1 and carry is 0 == 1
		  else if(value[i] == 1 && temp[i] == 0 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 0)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // both arrays have 1 and carry is 0 == 0
		  else if(value[i] == 1 && temp[i] == 1 && carry == 0)
		  {
			   temp[i] = 0;
			   carry = 1;
		  }
		  // both arrays have 0 and carry is 1 == 1
		  else if(value[i] == 0 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 1;
			carry = 0;
		  }
		  // one array has 1 and carry is 1 == 0
		  else if(value[i] == 1 && temp[i] == 0 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  else if(value[i] == 0 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 0;
			carry = 1;
		  }
		  // both arrays have 1 and carry is 1 == 1
		  else if(value[i] == 1 && temp[i] == 1 && carry == 1)
		  {
			temp[i] = 1;
			carry = 1;
		  }
		}
	}
	
	int y = 0;
    for(i = 31; i >= 0; i--)
    {
        checksum += temp[i] * power(2, y);
        y++;
    }

	if(flag == 4)
	{
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+1);
	}
    else if(flag == 1)
    {
        printf("X\n");
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+2);
    }
	else if(flag == 2)
	{
		printf("XX\n");
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+3);
	}
	else if(flag == 3)
	{
		printf("XXX\n");
		printf("%2d bit checksum is %8x for all %4d chars\n", checkSumSize, checksum, characterCount+4);
	}
    printf("\n");
	
	
  }
}//end of main
