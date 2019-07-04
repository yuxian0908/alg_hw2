#ifndef SPLIT_H
#define SPLIT_H
bool compare(int low, int up, int *x1, int sec_lower, int sec_upper);
void Split_H(Spolygon *s1, char *file_out);
void Split_V(Spolygon *s1, char *file_out);
struct RECT;
bool operator<(RECT a, RECT b);
#endif
