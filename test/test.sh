make
rm -f ./test/out.a
./minishell < ./test/commands.test > ./test/out.a

DIFF=$(diff ./test/out.a ./test/out.b) 
if [[ $DIFF != "" ]]; then
    printf "Erreur %s" "$DIFF"
else
    printf "OK\n"
fi