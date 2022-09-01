# ECOVID-19
2020년도 소프트웨어 경진대회 출품작 (장려상 수상) <br>
<br>
![](https://github.com/objectio/sfml-ECOVID-19/blob/master/README/%EC%9D%B8%ED%8A%B8%EB%A1%9C.jpg?raw=true)
 * 사용 언어: C++, 부분 C언어로 구현, SFML 라이브러리
 * 개발 툴: Dev-C++, Visual Studio 2019 Community
 * 디자인 툴: 프로크리에이트, Adobe Photoshop C
<br>

## 작품 개요
- 현재 코로나 바이러스가 유행하는 시국에서, 현대인들에게 일회용품 쓰레기들의 증가로 인해 야기되는 문제들(기후 변화, 지구 온난화)에 대한 경각심을 주는 것이 목표이다.
- 코로나 바이러스가 성행 중이지만 우리가 직면해있는 문제는 코로나 하나가 아니다. 당장의 문제를 해결하기 위해 이전부터 대두되어 왔던 환경 문제들을 등한시해서는 안된다는 걸 깨닫게 하는 것이 이 게임의 목표이다. 
- 일상생활 곳곳에서 빈번하게 쓰는 일회용품들을 사용함으로써 발생하는 부차적인 문제에 주목하였다. 전염을 막기 위해서 일회용품을 쓰는 것은 불가피한 일이기는 하나, 대중들이 다른 문제들에 대해서는 전혀 고려하지 않고 ‘코로나’만을 막기 위해 무분별하게 일회용품을 남용할 경우, 쓰레기 급증 그리고 그로 인해 기후 변화와 지구 온난화라는 문제가 야기될 수 있다는 것을 한번 더 생각하게끔 만들고 싶었다.
- 일회용품을 사용하는 것은 장기적으로 보았을 때, 그 사용량이 점점 누적되면 결국 우리의 삶에 치명적인 결과를 초래할 수 있다는 것을 계몽시키기 위함.
<br>

## 작품 내용
 - 사람 모습의 게임 캐릭터를 점프키로 조작하여 플레이하는 게임이다. 이 캐릭터는 현대인을 투영한다.
 - 집, 카페 등 현대인이 머물거나 방문하는 장소들을 게임에 구현하고, 그 장소에서 하는 일을 게임 내에 구현해 시각적으로 보여줌으로써 일상생활 속에서 우리가 미처 신경쓰지 못했던 쓰레기들이 얼마나 많이 발생하고 있는지 인지시킨다.
 - 점프키를 이용해 캐릭터에게 필요한 물품을 먹는다. 배고픔, 행복감 등의 게이지(이하 생체게이지라고 명명)가 0%가 되지 않도록 필요한 아이템을 드랍해야한다. 집 맵에 들어가게 되면 배달음식, 과자 등의 아이템이 생성되며 카페일 경우 커피, 디저트 등의 아이템이 나온다.
 - 맵에서 아이템을 먹으면 해당 아이템으로부터 쓰레기가 나와 누적된다. 예를 들어 카페 맵에서 커피 아이템을 먹을 경우 일회용 빨대, 일회용 용기 등이 누적되며 배달음식은 비닐봉지와 플라스틱 용기, 나무젓가락 등이 누적되는 식이다.
![](https://github.com/objectio/sfml-ECOVID-19/blob/master/README/disturbance.jpg?raw=true)
 - 쓰레기의 누적량이 많아질수록 최상단에 게이지로 구현된 지구의 HP가 줄어든다. HP게이지가 0이 되면 게임 오버가 된다. 
 - 캐릭터의 생체게이지와 지구의 HP게이지가 0으로 떨어지지 않도록 밸런스를 맞춰 유지하면서 최대한 오랫동안 게임 오버 되지 않도록 플레이하는 게임이다.
 ![](https://github.com/objectio/sfml-ECOVID-19/blob/master/README/%EA%B2%8C%EC%9E%84%20%EB%B0%A9%EB%B2%95%20%EC%86%8C%EA%B0%9C.JPG?raw=true)
 <br>
 
 ## 플레이 씬 이외의 게임 씬
 #### 게임 오버 창
 ![](https://github.com/objectio/sfml-ECOVID-19/blob/master/README/game%20over.jpg?raw=true)
 <br>
 <br>
 #### 최고 점수 확인 창
 ![](https://github.com/objectio/sfml-ECOVID-19/blob/master/README/highscore.jpg?raw=true)
 <br>
 <br>
 <br>
 
 ## 추진방법 및 일정
 #### ~ 20/06/26
 게임 초기구상을 마치고 그래픽 구현과 게임 아이콘 적용 등을 위해 SFML을 응용하기 위한 기본적인 내용들을 학습한다.
 
 #### 20/6/27 ~ 20/7/18
 Visual Studio와 Dev-C++ IDE에서 C언어와 C++언어로 캐릭터와 맵 구현 등의 게임 구조와 게임 구현을 끝마친다. 크롬의 이스터에그인 공룡 게임의 게임 코드를 응용하고, 맵 구현 및 각종 게이지 표현들은 여러 게임들의 오픈 소스를 참고할 예정이다. 

 #### 20/07/19 ~ 20/08/11
 게임에 필요한 아이콘과 그래픽 이미지를 프리소스 또는 자체 제작한 이미지로 입히고, C++ 라이브러리인 SFML를 이용하여 게임 내에 적용시킨다. 게임 아이콘 및 게임 내 그래픽 배경 작업은 프로크리에이트, Adobe Photoshop 등으로 작업하며, 그래픽 구현은 SFML로 구현한다.
 
 #### 20/08/12 ~ 20/08/16
 게임파일들을 패키징하여 실행파일 형식으로 만들어 배포 및 제출할 준비를 마친다. 게임을 구성하는데 필요했던 파일들과 게임 exe프로그램을 압축해서 제출할 예정이다.
 <br>
 <br>
 <br>
 
 ## 작품 활용도 및 기대효과
 현대 사회에서는 코로나를 막기에만 급급하고, 코로나 이외의 문제에는 다소 귀를 기울이지 않고 있다. 사실 깊이 살펴보면, 코로나로 인해 야기되는 다른 환경 문제들도 현대 사회에서 현재 발생하고 있는 실정이다. 코로나 이면의 다른 문제, 즉 코로나 바이러스로 인해 바뀐 우리의 생활방식이 환경 문제에 영향을 미칠 수 있다는 메세지를 전달하고 싶었다. <br>
사람들이 이 게임을 플레이하면서 캐릭터의 게이지와 지구의 HP게이지 간 균형을 어렵사리 맞추는 경험을 통해, 개발 측에서 보내는 환경보호 메세지를 잘 전달받기를 바란다.<br> 
코로나 바이러스가 더 퍼지지 막기 위한 활동 역시 중요하지만, 우리 현대인들은 코로나 바이러스로 인해 생길 수 있는 다른 문제들, 즉 코로나 바이러스의 이면의 문제들도 경각심을 갖고 인식하고 있어야한다고 생각하기 때문이다. <br>
  그래서 ECOVID-19 팀 측은 사람들이 이러한 저희의 메세지를 쉽게 알아채고 인식할 수 있도록, 스토리도 무난하게, 조작법도 간단하게 구성하였다. 이를 통해 남녀노소 많은 사람들이 이 게임을 재밌고 가볍게 즐겨줌으로써, 게임을 관통하는 이면의 무거운 메세지도 인식하기를 기대한다. 그럼으로써 사람들이 포스트 코로나 시대에, 환경문제도 한번은 더 생각해주는 데에 해당 게임이 기여하는 것을 목적으로 한다. 이를 통해 해당 작품이 후에 어린이들의 교육용으로도 활용되기를 기대한다. <br>
  
