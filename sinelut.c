#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

/* prints usage page */
void usage(char *pname)
{
    /* that's a loong printf! */
    fprintf(stderr,
        "fixpsine by Tomasz Watorowski (tw@mightydevices.com)               \n"
        "Build up an C array filled with sine data, prints on stdout        \n"
        "usage: %s [options]                                                \n",
        pname);
        
    /* split in two calls so that -Woverlength-strings does not complain */
    fprintf(stderr,
        "  -n \t\t number of array elements                                 \n"
        "  -a \t\t amplitude (def. max)                                     \n"
        "  -p \t\t sine period expressed in number of elements              \n"
        "  -s \t\t sine starting angle (relative to period)                 \n"
        "  -o \t\t additional offset                                        \n"
        "  -b \t\t bit width of a single array element (8, 16, 32)          \n"
        "  -l \t\t number of elements per line  (0 - single line output)    \n"
        );
}

/* program entry */
int main(int argc, char *argv[])
{
    /* number of elements, amplitude, period, starting angle, offset, bit 
     * width  */
    int n = 0, a = -1, p = 0, s = 0, o = 0, b = 8, l = 8;
    /* used for iterating over array elements*/
    int i;
    /* output format string */
    char of[20];
    /* currently processed command line option */
    int option;
    /* output array */
    uint32_t *out;
    
    /* no arguments? */
    if (argc < 2) {
        /* show usage screen */
        usage(argv[0]); return -1;
    }
    

    /* process all the options */
    while ((option = getopt(argc, argv,"n:a:p:s:o:b:l:")) != -1) {
        switch (option) {
        /* all parameters have numerical arguments */
        case 'n' : n = atoi(optarg); break; 
        case 'a' : a = atoi(optarg); break; 
        case 'p' : p = atoi(optarg); break;
        case 's' : s = atoi(optarg); break;
        case 'o' : o = atoi(optarg); break;
        case 'b' : b = atoi(optarg); break;
        case 'l' : l = atoi(optarg); break;
        /* unknown parameter */
        default :
            usage(argv[0]); return -1;
        break;
        }
    }
    
    /* try to allocate */
    if (n <= 0 || !(out = malloc(sizeof(uint32_t) * n))) {
        /* show error */
        fprintf(stderr, "Unable to allocate array of size %d\n", n);
        /* show usage screen */
        usage(argv[0]); return -1;
    }
    
    /* bit width */
    if (b != 8 && b != 16 && b != 32) {
        /* show error */
        fprintf(stderr, "Wrong bit width\n");
        /* show usage screen */
        usage(argv[0]); return -1;
    }
    
    /* none given? same as the number of elements */
    if (p == 0) 
        p = n;
        
    /* no amplitude? use the maximal amplitude determined by bit width */
    if (a == -1)
        a = 0x7FFFFFFF >> (32 - b);
    
    /* wrong amplitude period or starting angle */
    if (a < 0 || p < 0 || s < 0 || s >= p) {
        /* show error */
        fprintf(stderr, "Wrong amplitude period or starting angle\n");
        /* show usage screen */
        usage(argv[0]); return -1;
    }
    
    /* number of elements per line */
    if (l < 0) {
        /* show error */
        fprintf(stderr, "Wrong number of elements per line\n");
        /* show usage screen */
        usage(argv[0]); return -1;
    }
        
    /* process all the entries, using doubles here to prevent loosing precision 
     * when 32 bit output is desired. float has only 24 bits of mantissa. */
    for (i = 0; i < n; i++) {
        /* build up the sine angle */
        double ang = 2 * M_PI * (double)(i + s) / p;
        /* get the sine value */
        double val = (double)a * sin(ang) + (double)o;
        /* store value */
        out[i] = (uint32_t)val;
        /* mask out unused bits */
        if (b != 32)
            out[i] &= (1 << b) - 1;
    }
    
    /* prepare the output string */
    sprintf(of, "0x%%0%dx, ", b / 4);
    /* print the output */
    for (i = 0; i < n; i++) {
        /* print the number */
        printf(of, out[i]);
        /* magical end-of line formula */
        if (l && i % l == l - 1)
            puts("");
    }
    
    
    /* report success */
    return 0;   
}
