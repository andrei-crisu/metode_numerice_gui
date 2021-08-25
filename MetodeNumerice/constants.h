#ifndef CONSTANTS_H
#define CONSTANTS_H


//Obs: rolul acestor constante este
//de a autodocumenta codul
//astfel
// va fi mult mai util si usor pentru o parcurgere vizuala
//ulterioara a codului
//Codul va fi mult mai sugestiv

#define LETTER_ALLOWED true
#define NO_LETTER_ALLOWED false

#define DIGIT_ALLOWED true
#define NO_DIGIT_ALLOWED false

#define DIM_LIMIT 25
#define MAX_LINE DIM_LIMIT+1
#define MAX_COL DIM_LIMIT+1

#define EXTRACTION_FAILURE false
#define EXTRACTION_SUCCESSUFUL true

#define IS_SQUARE true
#define IS_NOT_SQUARE false

#define LEFT_ALIGNMENT 0
#define RIGHT_ALIGNMENT 1

#define LOWER_TRIANGULAR 0
#define UPPER_TRIANGULAR 1

#define STRICT_DOMINANCE true
#define WEAK_DOMINANCE false

#define ON_LINE true
#define ON_COLUMN false


#define HTML_ENTER " <br> "
#define DARK_RED "#D00000"
#define DARK_GREEN "#00C000"
#define DARK_BLUE "#274472"
#define KELLY_GREEN "#18A558"

//math symbols (unicode)
#define INTEGRAL_SYMBOL 0x222B
#define DINTEGRAL_SYMBOL 0x222C
#define LAMBDA_SYMBOL 0x03BB
#define DELTA_SYMBOL 0x0394

#endif // CONSTANTS_H
