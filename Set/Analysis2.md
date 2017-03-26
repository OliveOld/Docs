# 데이터 분석 결과보고 2

#### 분석 목표

#### 분석 진행
박동하 (luncliff@gmail.com )

## 요약

### 이전 요약
Training Set의 크기에 따른 결과를 볼 때, `NaiveBayes`의 정확도가 높아질 여지는 아직 있다고 생각된다. 오류 양상을 보면 보다 높은 정확도를 위해 추가적인 Attribute가 필요할 것으로 생각되며, `SVM` 속성을 별도로 분리하여 실험을 진행하는 것도 필요해 보인다.

## Background

## 분석 방법

> #### Signal Magnitude Area : SMA
> A statistical measure of **the magnitude of a varying quantity**.   
> ![Fig](https://wikimedia.org/api/rest_v1/media/math/render/svg/a49904e54957d30600c61f4adb00125378213ecb)

### Derived Values
분석에 사용된 유도값들은 다음과 같다.

#### Per TU
#### Per Group
 
### Train/Test set 구성
우선 이전의 실험 데이터를 양상에 따라 약 37개의 파일로 재구성하였다.

| Pattern   | Files |
|:---------:|------:|
| `idle`    | 7     |
| `walk`    | 9     |
| `active`  | 12    |
| `Trans`   | 9     |

#### Training Set
이를 조합해 Training(Learning) Set은 5개를 생성하였으며, 각각은 규모만 다를 뿐 `idle`, `walk`, `active`비율은 동일하도록 구성하였다.

| Set Name  | Scale |
|:---------:|------:|
| `L4`      | 8935  |
| `L5`      | 13258 |

#### Test set

추가로, Traning Set에 사용되지 않은 데이터들을 사용해 Test Set을 구성하였다. 이에 따라 Model을 생성하는데 사용된 데이터돠 검증하는데 사용되는 데이터 사이의 중첩이 없게 되었다.

Test Set은 1482개로 구성되었으며, 이는 가장 큰 Training Set인 `L5`의 약 1/10에 해당한다. Test Set 또한 Group의 크기 7, 17, 29 각각에 맞춰 생성하였다.


## 분석 결과
Modeling에는 Weka에 기본 내장된 `NaiveBayes`를 사용하였다. 

### Naive Bayes

| Train Set | Scale | 7      | 17     | 29     |
|-----------|------:|-------:|-------:|-------:|
| `L4`      | 8935  | 72.58% | 60.02% | 44.36% |
| `L5`      | 13258 | 74.34% | **76.43%** | 62.59% |


## 결론

