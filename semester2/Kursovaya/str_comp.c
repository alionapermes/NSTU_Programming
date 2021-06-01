// left is less => -1
// right is less => 1
int str_comp(const char* left, const char* right, int offset) {
    return ((left[offset]>right[offset])?-1:(((right[offset]>left[offset])?1:((offset<(strlen(left)<strlen(right)?strlen(left):strlen(right))))?str_comp(left,right,offset+1):(strlen(left)>strlen(right)?-1:1))));
}
