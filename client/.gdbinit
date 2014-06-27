file main
target remote localhost:1234
break main
display/4i $pc
cont
