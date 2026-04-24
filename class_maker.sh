#!/bin/bash

# Verifica se passaste o nome da classe
if [ -z "$1" ]; then
    echo "Uso: ./class_maker.sh <NomeDaClasse>"
    exit 1
fi

CLASS_NAME=$1
HPP_NAME="${CLASS_NAME}.hpp"
CPP_NAME="${CLASS_NAME}.cpp"
UPPER_NAME=$(echo "$CLASS_NAME" | tr '[:lower:]' '[:upper:]')

# --- GERAR O FICHEIRO .HPP ---
cat << EOF > $HPP_NAME
#ifndef ${UPPER_NAME}_HPP
# define ${UPPER_NAME}_HPP

# include <iostream>
# include <string>

class $CLASS_NAME {
    private:
        // Atributos aqui
    public:
        $CLASS_NAME();
        $CLASS_NAME(const $CLASS_NAME& other);
        $CLASS_NAME& operator=(const $CLASS_NAME& other);
        ~$CLASS_NAME();
};

#endif
EOF

# --- GERAR O FICHEIRO .CPP ---
cat << EOF > $CPP_NAME
#include "$HPP_NAME"

$CLASS_NAME::$CLASS_NAME() {}

$CLASS_NAME::$CLASS_NAME(const $CLASS_NAME& other) {
    *this = other;
}

$CLASS_NAME& $CLASS_NAME::operator=(const $CLASS_NAME& other) {
    if (this != &other) {
        // Copiar atributos aqui
    }
    return *this;
}

$CLASS_NAME::~$CLASS_NAME() {}
EOF

echo "✅ Classe $CLASS_NAME criada com sucesso ($HPP_NAME e $CPP_NAME)!"
