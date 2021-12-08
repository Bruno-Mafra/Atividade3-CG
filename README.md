# Atividade 3 - Computação Gráfica

Esse repositório contém o código-fonte de uma aplicação gráfica interativa 3D com texturização e iluminação feita para a disciplina de Computação Gráfica da UFABC (DA1MCTA008-17SA) ministrada por Bruno Marques (2021).

## Red Light - Green Light
Essa aplicação gráfica é um aperfeiçoamento da atividade 2 já apresentada anteriormente. Para essa versão foi adicionado iluminação e texturização para os elementos da cena, resultando em uma visualização mais realista e de maior qualidade.

### Como jogar
Utilize as setas direcionais ou as teclas 'W', 'S', 'Q', 'E' para controlar a camera para frente, para trás, para a esquerda e para a direita respectivamente. As teclas 'A' e 'D' controlam a rotação da camera em torno do próprio eixo permitindo uma melhor visualização dos objetos do cenário. O objetivo é atravessar a linha de chegada (linha branca) para obter a vitória, diferentemente do jogo original, essa versão não tem tempo para finalizar o percurso. Você pode jogar através da github-page associada a esse repositório ou no link: https://bruno-mafra.github.io/Atividade3-CG/

### Como compilar
Para compilar o código-fonte disponibilizado nesse repositório diretamente no seu computador é necessário fazer a configuração do ambiente apresentada no início da disciplina e adicionar a pasta "greenredlight" (que está na pasta 'Código-Fonte' desse repositório) no diretório examples do abcg. Também é necessário adicionar o arquivo CMakeLists.txt nesse mesmo diretório. Depois disso é so compilar no terminal para gerar o executável.

## Conteúdo e Técnicas utilizadas

Como essa atividade é um aperfeiçoamento, muitas das técnicas utilizadas nesse projeto já foram descritas anteriormente no projeto 2. Por esse motivo, serão apresentadas a seguir somente as novas implementações realizadas em cada classe (objetos da cena).

### camera.cpp
Essa classe agora também é responsável pela definição das variaveis uniformes relacionadas a iluminação que são utilizadas por todos os objetos da cena, ela também define os atributos de direção da luz e suas cores. Para esse projeto a luz é branca pois a ideia é que reprensente uma fonte de luz natural como o sol.

### boneca.cpp
Essa classe agora carrega uma textura difusa que detalha adequadamente a aparência da boneca. Essa textura utliza a técnica de mapeamento UV.

### <strike>arvore.cpp</strike> 
Essa classe não existe mais, pois a texturização da arvore toda envolvia dois materiais diferentes (um para o tronco e outro para folhas), agora, então, foram adicionadas duas novas classes que fazem a leitura separada dos .obj relacionado a arvore e seus respectivos materiais.

### tronco.cpp
Essa nova classe é responsável por ler o .obj do tronco de uma arvore, além de carregar as texturas difusa e normal desse objeto utilizando a técnica de mapeamento UV.

### folhas.cpp
Essa nova classe é responsável por ler o .obj das folhas de uma arvore, além de carregar as texturas difusa e normal desse objeto utilizando a técnica de UV mapping. A textura difusa, nesse caso, é uma "alpha textura" que apresenta transparência nas regiões de "vazio" entre as folhas, por esse motivo, essa classe também implementa a técnica de "Blending" do OpenGL.

Outro detalhe é que a face traseira de alguns triângulos (que representam as folhas) aparecem de frente para a câmera, resultando em tonalidades de vermelho como é esperado pelo shader utilizado. Já que esse shader é o mesmo de outros objetos da cena e seria desnecessário criar um novo para renderizar apenas um objeto, isso foi corrigido renderizando o .obj das folhas duas vezes alternando a orientação (lado da frente) dos triângulos e descartando as traseiras com CULL FACE. 

### soldado.cpp
Essa classe agora carrega uma textura difusa e uma textura normal que detalham adequadamente a aparência do soldado. Essas texturas utlizam a técnica de mapeamento UV. Além disso, foi utilizado um filtro mipmap para melhorar a qualidade do soldado que ficava estranha quando muito distante.

### bonecos.cpp
Essa classe agora carrega uma textura difusa e uma textura normal que detalham adequadamente a aparência dos bonecos. Essas texturas utlizam a técnica de mapeamento UV.

### ground.cpp
Essa classe agora carrega uma textura difusa e uma textura normal que dão ao chão a aparência de areia, assim como é no jogo original. Essas texturas utlizam a técnica de mapeamento UV. Para melhorar a qualidade da textura quando aplicada, o .obj do chão é varias vezes renderizado como se fossem pisos de tamanho normalizado.

### paredes.cpp
Essa classe agora carrega uma textura difusa e uma textura normal que detalha a aparência da parede deixando similar a algum tipo de gesso pintado em um tom de azul. Como o .obj foi feito por mim no blender e não tem coordenada de texturas é utilizado a técnica de mapeamento planar.

---

## Shaders
Esse projeto faz uso de 3 tipos diferentes de shaders. Isso ocorre pois o .obj da boneca, por exemplo, não apresenta textura normal e isso compromete aspectos de iluminação quando renderizado fazendo uso de shader que utiliza essa textura. A linha de chegada também é um objeto 3D muito simples, que não apresenta nenhuma textura, mas necessita de um atributo de cor, por isso foi utilizado um shader separado para esse objeto.

O shader "normalmapping.frag" sofreu uma pequena alteração na parte do cálculo de mapeamento planar na direção X e Z (onde estão as paredes da cena). Essa alteração faz com que a textura, quando aplicada no .obj das paredes, seja reproduzida em um "tamanho menor", posteriormente, o GL_REPEAT vai ser forçado a repetir mais vezes a textura no .obj (empacotamento). Isso resulta numa qualidade visual melhor para a textura, já que sem isso ela aparenta distorcida devido a escala do objeto na cena.

---

## Resultado
O resultado final é uma versão parecida com a anterior, até mesmo nas cores, mas texturizada e muito mais bonita visualmente.

![result](https://user-images.githubusercontent.com/74402232/145303708-2a0cef8c-3c34-4a95-bdf5-7683f0a8b5d9.png)


**Obs:** Algumas texturas foram modificadas se comparadas ao link original de download. Isso foi feito através do Photoshop para que ficassem na cor adequada que combinasse mais com o projeto. Exemplo: os "bonecos among us" eram orginalmente vermelhos e foram alterados para uma cor verde/ciano. Também ocorre na cor das paredes e nas folhas da arvore.

---
## Fonte dos Modelos 3D (incluindo textura)
A partir desses links é possível visualizar e baixar os modelos 3D usados nesse projeto, são todos gratuitos ou para uso não comercial.

[Link do modelo 3D da boneca](https://sketchfab.com/3d-models/squid-game-doll-ccfed977f35446a7914a3abc5e393182)

[Link do modelo 3D da árvore](https://sketchfab.com/3d-models/tree-a2a6237a270840e198cc7db1c47f1ef7)

[Link do modelo 3D do soldado](https://sketchfab.com/3d-models/squid-game-pinksoldier-8f6112f88ea743e8a468ac017bb2c0e2)

[Link do modelo 3D do boneco (Among Us)](https://sketchfab.com/3d-models/among-us-obj-5254d257fac74e28aa1455a368481279)

## Fonte de Texturas Adicionais 
[Link da textura de areia](https://sketchfab.com/3d-models/beach-sand-substance-5c08ab068a6c48ca9c07c2eb396ece2a)

[Link da textura de gesso](https://polyhaven.com/a/yellow_plaster)

---
Mais detalhes sobre a aplicação podem ser obtidos acessando o código-fonte.

---

**RA:** 11201811147                                                                                                                                                             
**Aluno:** Bruno Francisco Rodrigues Mafra            
