# Atividade 3 - Computação Gráfica

Esse repositório contém o código-fonte de uma aplicação gráfica interativa 3D com texturização feita para a disciplina de Computação Gráfica da UFABC (DA1MCTA008-17SA) ministrada por Bruno Marques (2021).

## Red Light - Green Light
Essa aplicação gráfica é um aperfeiçoamento da atividade 2 já apresentada anteriormente. Para essa versão foi adicionado iluminação e texturização para os elementos da cena, resultando em uma visualização mais realista e de maior qualidade.

### Como jogar
Utilize as setas direcionais ou as teclas 'W', 'S', 'Q', 'E' para controlar a camera para frente, para trás, para a esquerda e para a direita respectivamente. As teclas 'A' e 'D' controlam a rotação da camera em torno do próprio eixo permitindo uma melhor visualização dos objetos do cenário. O objetivo é atravessar a linha de chegada (linha branca) para obter a vitória, diferentemente do jogo original, essa versão não tem tempo para finalizar o percurso. Você pode jogar através da github-page associada a esse repositório ou no link: https://bruno-mafra.github.io/Atividade3-CG/

### Como compilar
Para compilar o código-fonte disponibilizado nesse repositório diretamente no seu computador é necessário fazer a configuração do ambiente apresentada no início da disciplina e adicionar a pasta "greenredlight" (que está na pasta 'Código-Fonte' desse repositório) no diretório examples do abcg. Também é necessário adicionar o arquivo CMakeLists.txt nesse mesmo diretório. Depois disso é so compilar no terminal para gerar o executável.

## Conteúdo e Técnicas utilizadas

O cenário é constituido por varios objetos 3D (arquivos .obj). Cada um dos diferentes objetos é lido por uma classe específica também responsável por gerar seus respectivos VBO's e VAO's. A classe openglwindow.cpp gerencia uma instância dessas demais classes que compõem o cenário. Alguns dos objetos 3D foram obtidos online em algum formato de arquivo 3D qualquer e posteriormente convertidos para o formato .obj com o software blender.

### camera.cpp
A visão da camera no jogo é em primeira pessoa e a posição da câmera no espaço do mundo representa a posição de um observador nesse espaço. Para esa representação a projeção perspectiva é bastante adequada. Os parâmetros da matriz de projeção são semelhantes aos vistos em aula, o volume de visão precisou ser aumentado para que todo o conteúdo da cena pudesse aparecer adequadamente sem ser cortado. Essa classe também é responsável pela colisão com as paredes, impedindo que o observador (câmera LookAt) "saia para fora" do espaço delimitado pela sala, e por impedir a movimentação quando o jogador for eliminado.

### boneca.cpp
Responsável por ler o .obj da boneca de Round 6, essa classe também faz todo o controle do comportamento da boneca através do método update(). A boneca deve girar em 180 graus em torno do eixo Y (equivale a estar para frente ou para trás) por uma quantidade aleatoria de tempo definida por uma função estilo random.

### arvore.cpp
Responsável por ler o .obj de uma arvore, assim como na série, no cenário criado a boneca fica na frente de uma arvore.

### soldado.cpp
Responsável por ler o .obj do soldados que aparecem em Round 6, assim como na série, existem dois soldados um de cada lado da boneca olhando para os jogadores.

### bonecos.cpp
Responsável por ler o .obj de bonecos que representam os jogadores. Esses bonecos na verdade são do jogo 'Among Us', mas combinam com os outros elementos no estilo chibi/cartoonizado, fazendo mais sentido que um modelo de humano. Esses bonecos tem as cores do uniforme dos jogadores na série e aparecem em grande quantidade no cenário.

### ground.cpp e walls.cpp
Responsável por ler o .obj do chão e das paredes do cenário respectivamente. Esses objetos 3D foram criados por mim no software 'blender' e representam estruturas simples, são como faces recortadas de um cubo unitário. Apesar de serem apenas faces (são como folhas de papel no cenário 3D), optei por representar atráves de arquivos .obj pensando no projeto 3 e em uma possível adição de texturas.

### listra.cpp
Responsável por renderizar uma listra branca no chão que representa a linha de chegada. Por ser muito simples não necessita de ler um arquivo .obj.

### gamedata.cpp
Por ser um jogo, esse projeto reutiliza o arquivo gamedata.cpp do asteroids que define estados do jogo como "Playing", "GameOver" e "Win".

---

O resultado final é uma versão que lembra bastante o episódio da série numa versão reduzida em uma espécie de sala no "espaço do mundo". A classe openglwindow.cpp, além de gerenciar instâncias das outras classas, também usa a função PaintUI() para exibir as mensagens do jogo na tela e o status de 'Green Ligth - Red Light' numa fonte de tamanho e cores personalizados.

![result](https://user-images.githubusercontent.com/74402232/142194124-ab5329fd-f30e-4813-8dd6-80d04c8eef23.png)


**Obs:** Todas as classes que renderizam arquivos .obj também são responsáveis pela atribuição de cores e por aplicar matrizes de transformação nos elementos da cena como posição, rotação e escala.

---
## Fonte dos Modelos 3D (incluindo textura)
A partir desses links é possível visualizar e baixar os modelos 3D usados nesse projeto, são todos gratuitos ou para uso não comercial.

[Link do modelo 3D da boneca](https://sketchfab.com/3d-models/squid-game-doll-ccfed977f35446a7914a3abc5e393182)

[Link do modelo 3D da árvore](https://sketchfab.com/3d-models/tree-a2a6237a270840e198cc7db1c47f1ef7)

[Link do modelo 3D do soldado](https://sketchfab.com/3d-models/squid-game-pinksoldier-8f6112f88ea743e8a468ac017bb2c0e2)

[Link do modelo 3D do boneco (Among Us)](https://sketchfab.com/3d-models/among-us-obj-5254d257fac74e28aa1455a368481279)

---
Mais detalhes sobre a aplicação podem ser obtidos acessando o código-fonte.

---

**RA:** 11201811147                                                                                                                                                             
**Aluno:** Bruno Francisco Rodrigues Mafra            
