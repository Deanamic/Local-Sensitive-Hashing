((cnt=1))
for i in ./*.story; do
    mv ${i} cnn.dat${cnt};
    ((cnt++));
done
