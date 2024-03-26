#!/bin/bash
 
 function execute(){
  gcc -o teste teste.c
  ./teste
}

 function trataErro(){
  echo "OCorreu uma falha de segmentação, vou executar novamente ... $1"
  execute
 }
 
trap 'trataErro "222"' EXIT

#trap 'trataErro' ERR
execute