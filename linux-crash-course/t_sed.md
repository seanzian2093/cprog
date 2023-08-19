# Manipulate strings using regular expression

* Search and replace

`sed 's/Pineapple/Feta/' toppings.txt`

## use -i flag for inplace replace
`sed -i 's/Pineapple/Feta/' toppings.txt`

* Delimiter is flexable

`sed 's.Pineapple.Feta.' toppings.txt`

* Remove
`sed 's/Pineapple//' toppings.txt`

`sed 's./etc..' paths.txt`
