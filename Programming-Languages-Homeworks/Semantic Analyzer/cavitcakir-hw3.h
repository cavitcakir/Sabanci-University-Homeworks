#ifndef __CAVITCAKIRHW3_H
#define __CAVITCAKIRHW3_H
typedef enum { SCA, VEC, MAT, ROW, ROWS } NodeType;
extern int line_count;
typedef struct my_node {
  int Col;
  int Row;
  NodeType Type;
} my_node;

#endif
