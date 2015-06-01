int main(){
  int test = 30;
  int i =0;
  while(i<10){
    test = test -1;
    i= i+1;
    if(i%2 == 0){
      test = test -1;
    }
  }
}
