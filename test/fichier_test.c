/*
 * Cette fonction ne sert a rien 
 */
intmain(int arg) {
  const int MACHIN =12;
  int i_1 = 0, test;
  arg = arg *2;
  if(arg < 0) {
    return arg;
  }
  else {
    i_1 = (i_1 / arg) % MACHIN;
    i_1 = i_1 * i_1;
    printf(i_1);
  }
  return i;

}
