/*
CS+ V4.00.00  [15 Mar 2016] [Watch Information]
Samstag, 18. Juni 2016 23:57:52
Debug Tool :RX E1(Serial)
Project Name :fc-0.0.0
*/

/* Example */
/*
full_matrix data:
  [0]                 1.100000E+0 float(4)                                    
  [1]                 1.200000E+0 float(4)                                    
  [2]                 1.300000E+0 float(4)                                    
  [3]                 1.400000E+0 float(4)                                    
  [4]                 2.100000E+0 float(4)                                    
  [5]                 2.200000E+0 float(4)                                    
  [6]                 2.300000E+0 float(4)                                    
  [7]                 2.400000E+0 float(4)                                    
  [8]                 3.100000E+0 float(4)                                    
  [9]                 3.200000E+0 float(4)                                    
  [10]                3.300000E+0 float(4)                                    
  [11]                3.400000E+0 float(4)                                    
  [12]                4.100000E+0 float(4)                                    
  [13]                4.200000E+0 float(4)                                    
  [14]                4.300000E+0 float(4)                                    
  [15]                4.400000E+0 float(4)                                    
  nRows               0x0004  uint16_t(2)                  
  nCols               0x0004  uint16_t(2)

mask data (Vector_ui8)
  [0]                 0x00  uint8_t(1)
  [1]                 0x01  uint8_t(1)
  [2]                 0x00  uint8_t(1)
  [3]                 0x01  uint8_t(1)

result_matrix data:
  [0]                 2.200000E+0 float(4)                                    
  [1]                 2.400000E+0 float(4)                                    
  [2]                 4.200000E+0 float(4)                                    
  [3]                 4.400000E+0 float(4)                                    
  [4]                 0.000000E+0 float(4)                                    
  [5]                 0.000000E+0 float(4)                                    
  [6]                 0.000000E+0 float(4)                                    
  [7]                 0.000000E+0 float(4)                                    
  [8]                 0.000000E+0 float(4)                                    
  [9]                 0.000000E+0 float(4)                                    
  [10]                0.000000E+0 float(4)                                    
  [11]                0.000000E+0 float(4)                                    
  [12]                0.000000E+0 float(4)                                    
  [13]                0.000000E+0 float(4)                                    
  [14]                0.000000E+0 float(4)                                    
  [15]                0.000000E+0 float(4)                                    
  nRows               0x0002  uint16_t(2)                  
  nCols               0x0002  uint16_t(2)
*/

/* Constant definitions  */

#define VECTOR_SIZE         32                          // max size of verctors
#define MATRIX_SIZE         VECTOR_SIZE * VECTOR_SIZE   // max. size of matrices
#define MATRIX_CNT          20                          // max. count of matrices


/* global vars   */

float Matrix_f[MATRIX_CNT][MATRIX_SIZE];        // 2d matrice array, float
uint8_t  Vector_ui8[VECTOR_CNT][VECTOR_SIZE];   // 2d vector array, uint8_t


/* Typedef definitions  */

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;

typedef struct 
{ 
    uint16_t nRows;
    uint16_t nCols; 
    void *   data; 
} matrix_t; 


/* Functions  */

void init_matrix_slice(void)
{
    int result;                         // error val
    int row = 4, col = 4;               // matrice size
    float * mdatap;                     // pointer to matrice data
    matrix_t matrix_full, matrix_result;// define matrice, data = pointer to data, nRows, nCols
    
    /* define the matrix */
    mdatap = &Matrix_f[0][0];   // get pointer to matrice data [0,0]
    matrix_full.data = mdatap;  // store pointer to matrice data
    matrix_full.nRows = row;    // store number of rows
    matrix_full.nCols = col;    // store number of cols
    *mdatap++ = 1.1;            // store 1.1 matrice data
    *mdatap++ = 1.2;            // store 1.2 matrice data
    *mdatap++ = 1.3;            // store 1.3 matrice data
    *mdatap++ = 1.4;            // store 1.4 matrice data
    *mdatap++ = 2.1;            // store 2.1 matrice data
    *mdatap++ = 2.2;            // store 2.2 matrice data
    *mdatap++ = 2.3;            // store 2.3 matrice data
    *mdatap++ = 2.4;            // store 2.4 matrice data
    *mdatap++ = 3.1;            // store 3.1 matrice data
    *mdatap++ = 3.2;            // store 3.2 matrice data
    *mdatap++ = 3.3;            // store 3.3 matrice data
    *mdatap++ = 3.4;            // store 3.4 matrice data
    *mdatap++ = 4.1;            // store 4.1 matrice data
    *mdatap++ = 4.2;            // store 4.2 matrice data
    *mdatap++ = 4.3;            // store 4.3 matrice data
    *mdatap++ = 4.4;            // store 4.4 matrice data

    /* define the slice vector */
    Vector_ui8[0][0] = 0;
    Vector_ui8[0][1] = 1;
    Vector_ui8[0][2] = 0;
    Vector_ui8[0][3] = 1;

    /* clear result matrice */
    memset(&Matrix_f[1][0], 0, sizeof(Matrix_f[1]));

    /* define result matrice */
    matrix_result.data = &Matrix_f[1][0];
    matrix_result.nCols = 0;
    matrix_result.nRows = 0;
    
    /* slice the vector */
    result = slice_bool(&matrix_full, &Vector_ui8[0][0], &matrix_result);
}


int slice_bool(matrix_t * full_matrix, uint8_t * mask, matrix_t * result_matrix)
{
    int row, col, res_row = 0, res_col = 0, rflg = 0, cflg = 0;
    int result = -1;
    float * md_ptr, * result_matrix_ptr = result_matrix->data;
    uint8_t * row_mask, * col_mask;
    md_ptr = (float *)full_matrix->data;
    
    /* Error if number of rows or cols = 0 */
    if (full_matrix->nRows != 0x00 && full_matrix->nCols != 0x00)
    {
        row_mask = mask; // use mask for row
        for (row = 0; row < full_matrix->nRows; row++)
        {
            col_mask = mask; // use mask for col
            for (col = 0; col < full_matrix->nCols; col++)
            {
                if (*col_mask != 0 && *row_mask != 0)
                {
                    *result_matrix_ptr++ = *md_ptr; // keep relevant data in result matrice
                    
                    /* calc number of rows & cols in result matrice */
                    if (res_row == 0 && res_col == 0)
                    {
                        res_col++;
                        res_row++;
                        cflg = col;
                        rflg = row;
                    }
                    if (col > cflg)
                    {
                        res_col++;
                        cflg = col;
                    }
                    if (row > rflg)
                    {
                        res_row++;
                        rflg = row;
                    }
                }
                col_mask++; // increment pointer to next col mask data
                md_ptr++; // increment pointer to next result matrice data
            }
            row_mask++; // increment pointer to next row mask data
        }
        result = 0x00; // no errors
        result_matrix->nRows = res_row; // return number of rows in result matrice
        result_matrix->nCols = res_col; // return number of cols in result matrice
    }
    return result;
}


