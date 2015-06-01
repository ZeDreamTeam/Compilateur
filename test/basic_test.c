int main() {
  int maVar1=0;
  int maVar2;
  while(maVar1 < 10) {
    maVar2 = 0;
    while(maVar2 < 10) {
      maVar2 = maVar2 + 1;
    }
    maVar1 = maVar1 + 1;
  }
  if(maVar1 == maVar2) {
    maVar1 = 5;
  } else {
    maVar1 = 10;
  } 
}
