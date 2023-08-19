# ./svmsg_create -p
./svmsg_send 1 20 "I hear and I forget."
./svmsg_send 1 10 "I see and I remember."
./svmsg_send 1 30 "I do and I understand."
./svmsg_receive -t -20 1
./svmsg_receive -t -20 1
./svmsg_receive -t -20 1
./svmsg_receive 1