#
#  Apply the following actions on lines without a preceding < 
#  symbol, which implies a xml tag

/^[ \t]*<.*/!{

   # preprocess
   ## delete preceding blanks and tabs
   s/^\([ \t]\)*\(.*\)/\2/g

   ## delete //comment 
   /\/\/.*/d

   ## delete /*comment*/
   /\/\*.*\*/d 

   ## delete blank line
   /^$/d

   ## remove the preceding and trailing blanks
   ## around '{', '}', '(', ')', ',', ';'  
   s/ \?\([{}(),;]\) \?/\1/g
   
   ## remove the preceding and trailing blanks
   ## around normal operators
   ##  +, ++, -, --, *, *=, /= , >, >=, <=, |
   ## ||, &, && 
   s/ \?\([\+\-\*\/\=\<\>\|\&]\) \?/\1/g
 
   # do the substitution 
   ## substitute quotation
   s/\"/\&#0034;/g

   ## substitute ampersand
   s/\&/\&#0039;/g

   ## substitute less than
   s/</\&#0060;/g

   ## substitute greater than
   s/>/\&#0062;/g

   ## substitute blank
   s/ /\&#x0020;/g

   ## substitute end-of-line with newline entity
   s/\(.*\)$/\1\&#x000A;/g 
}
