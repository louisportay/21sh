echo "`wc -l **/*.[ch] **/Makefile | tail -1 | awk '{print $1}'` lines in `find . -type f -regex '.*\.[ch]' | wc -l | awk '{print $1}'` files"
