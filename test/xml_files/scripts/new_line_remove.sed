
/^[^<]*$/{
 # append  pattern space to hold space
 # H
 # copy from hold space
 # g 
 # remove new line
 # s/\n//
  :top
  N
  /^[^<]*$/{
    s/\n//
  }
  
  # Just jump, not has any other action, for example
  # no print
  /^[^<]*$/b top   
 
  # When flow reaches here default behavior print will
  # be executed   
}
