# Matemática Discreta 2

Um estudante está desenvolvendo uma função de segurança para validar acessos em um sistema. Essa função baseia-se
na ideia de "verificação modular", utilizando os conceitos de congruência, primalidade, coprimalidade, Pequeno
Teorema de Fermat, Teorema de Euler e exponenciação modular eficiente.

Porém, o sistema da escola do professor utiliza um método especial para definir a base da potência. Ao invés desta
fornecida diretamente, o valor da base a é definido como o resultado da divisão modular entre dois elementos de
Zn:

(Ex: 38⊘79 em Z252 , generalizando: H⊘G em Zn )

Implemente um programa em C que tenha (dados de entrada):

  • Três números inteiros positivos H, G e n, usados para calcular a base a

  • Um expoente x

  • Um módulo n1

CALCULAR: a^x mod n1
