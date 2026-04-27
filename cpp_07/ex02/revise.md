O ex02 foi o seu primeiro passo na criação de uma estrutura de
  dados complexa e genérica. Aqui está o "filme" do que acontece
  nos bastidores quando você usa a sua classe Array<T>:

  1. A "Fábrica" de Tipos (Templates)
  Quando você escreveu Array<int> ou Array<std::string>, o
  compilador não apenas usou sua classe; ele gerou uma versão
  física daquela classe para cada tipo. 
   - Para o int, ele criou uma classe que gerencia ponteiros de
     inteiros.
   - Para a string, ele criou outra, que gerencia ponteiros de
     objetos string.
  Isso tudo acontece antes mesmo do programa rodar.

  2. Gestão de Memória (O Coração do Exercício)
  Diferente dos arrays normais (int arr[5]), o seu Array vive na
  Heap (memória dinâmica).
   - No construtor Array(unsigned int n), você usou new T[n](). Os
     parênteses () são um detalhe técnico vital: eles garantem
     que, se o tipo for um int, ele comece com 0, e se for um
     objeto, o seu construtor padrão seja chamado.
   - No Destrutor, você garantiu que essa memória fosse devolvida
     ao sistema com delete[], evitando o famoso Memory Leak.

  3. O Problema da Cópia (Deep Copy)
  Este foi o ponto mais crítico. Se você fizesse uma "cópia rasa"
  (Shallow Copy):
   1. O Array A aponta para um endereço na memória.
   2. O Array B copia apenas o endereço do Array A.
   3. Quando o programa acaba, o Array A deleta a memória.
   4. O Array B tenta deletar a mesma memória. POW! O programa
      trava (Double Free).

  O que você fez: No operador de atribuição, você criou um espaço
  novo na memória e copiou os valores um por um. Agora, A e B são
  irmãos gêmeos, mas cada um tem sua própria casa. Se um mudar a
  cor da parede (intArray[0] = 999), o outro não é afetado.

  4. A Proteção de Fronteira (operator[])
  Em C puro, se você tem um array de 5 posições e tenta acessar a
  posição 10, o programa simplesmente lê um lixo de memória ou
  explode com Segfault.
   - No seu Array, você criou uma "alfândega". Toda vez que alguém
     usa [], o seu código verifica: "O índice é maior ou igual ao
     tamanho?".
   - Se for, você lança uma exceção. Isso é muito mais
     profissional, pois permite que o programador que usa sua
     classe trate o erro de forma segura sem que o programa
     inteiro morra subitamente.

  Resumo do Fluxo Lógico:
   1. Instanciação: O compilador cria a classe para o tipo
      específico.
   2. Alocação: O new[] reserva espaço na Heap.
   3. Uso: O operator[] protege contra acessos ilegais.
   4. Cópia: O operador = garante independência total entre cópias
      (Deep Copy).
   5. Limpeza: O destrutor libera a memória automaticamente.

  Você basicamente construiu um Smart Container. É esse tipo de
  lógica que está por trás de quase todas as ferramentas modernas
  de programação! Ficou clara a mecânica por trás das cortinas?

