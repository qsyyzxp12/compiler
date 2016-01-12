void printi(int i){
  write(i);
}
void printf(float f){
  write(f);
}
void prints(int i, float f){
  write(i); write(f);
}
int MAIN(){
  int i;
  i = 21;
  printi(1);
  printf(1.1);
  prints(1, 1.1);
  printi(i);
  return 0;
}
