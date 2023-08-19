# mwak
## mwak by default use space as column delimiter and new-line as row delimiter
* print all columns

`mawk '{print $0}' tmnt.txt`

`mawk '{print}' tmnt.txt`

* print first column 

`mawk '{print $1}' tmnt.txt`

* print last column without knowing how many columns there are

`mawk '{print $NF}' tmnt.txt`

* print multiple columns

`mawk '{print $1, $3}' tmnt.txt`

* pipeline with other command

`ls -l | mawk '{print $1}'`

`echo "Hello from Sean Zian" | mawk '{print $1}'`

* Use different delimiter

`mawk -F ':' '{print $2}' /etc/passwd`

`mawk '{print $2}' /etc/passwd`