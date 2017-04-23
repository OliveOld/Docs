# Canine Posture Detection based on a Triaxial Accelerometer
> 3축 가속도계 기반 반려견 자세 인지

### Keywords
Canine Behavior, Motion Analysis, Classification, Accelerometer

### Abstract(프로젝트 요약)
반려동물 행동 인지를 위해 목 전면에 부착 가능한 웨어러블 기기와 이로부터 기록된 값을 받아 사용자에게 효과적으로 보여줄 수 있는 모바일 어플리케이션을 개발하였다.
기기는 반려동물의 동작에 따른 가속도 변화를 감지하고, 내장된 알고리즘을 사용하여 자세와 방향을 분류, 누적시킨다. 
보드는 Punch Through 社의 Arduino Bean을 사용했으며 이를 담는 케이스를 제작하였다. 기기는 목줄에 부착하여 사용할 수 있으며, 총 무게는 약 20g으로 반려견의 부담을 최소화 하였다.
누적된 결과는 모바일 어플리케이션으로 전송되며, 사용자가 받아들이기 편한 도표로 변환한다. 기기와 어플리케이션의 송수신은 블루투스를 사용한다.

## 1. Introduction

#### 대상 문제는 무엇인가?
반려견 활동량 측정. 혼자 있는(고립된) 반려견의 상태 확인

#### 관련연구들의 주요 목적
훈련 / 상태 모니터링
> 대인 모니터링과의 차이는?

#### 기존 연구의 문제는?
착용 부위, Receiver(Base Station) 중심 접근. 착용 기기는 센서의 값을 전송하는 역할만을 수행하며, 이를 별도로 수신받는 측에서 분석하는 방식으로 진행됨. 이런 점은 측정과 분석을 분리시킨 것. 

하지만 홀로 가택에 고립된 반려견으로부터 획득한 정보를 저장하기 위해 별도로 수신장치를 사용하는 것은 비용부담, 불편한 사용자 인터페이스가 될 수 있음. 
이 연구에서는 궁극적으로 반려견이 착용하는 기기에서 측정과 분석을 동시에 수행하는 것을 목표로 하였음.

### Section

향후 구성에 따라 변경. 특히 3과 4는 논리 전개에 따라 서로 바뀔 가능성이 있음.

 1. 도입
 1. 관련연구
 1. 시스템 설계
 1. 내장 알고리즘
 1. 실험
 1. 논의
 1. 결론

## 2. Related Works
> 생략함 차후 추가

## 3. System Design
> 센서 디바이스와 시스템 구성도

### 3.1. Application
> 사용자 인터페이스인 Mobile App에 대하여


### 3.2. Device
#### 구성(Components)
> Dimension는 차후 케이스 포함한 정보로 변경

보드는 Light Blue Bean을 사용하였다. 케이스는 Siemens社의 NX 를 이용하여 도면을 그렸으며, Ultimaker社의 CURA를 이용하여 출력하였다.

 - Processor / Memory : ATmega328p 8Mhz, 2KB SRAM
 - Accelerometer / Sensitivity : Digital 3-axis BMA250
 - Communication : Bluetooth 4.0 LE
 - Battery : 리튬 Coin Cell  CR2032 3V 225mAh
 - Dimension / Weight : 45.7mm x 20.5mm x 8.5mm / 20 g


### 3.3. 착용부위(Placement)
케이스는 스트랩을 사용하여 반려견 몸에 밀착하게 착용할 수 있도록 하였다. 주요 착용부위로는 목 앞쪽을 전제하였다.

> 등쪽/목 앞쪽이 가장 예측이 좋았다는 선행 연구를 따른 것. 

**착용 이미지**


> 실험 대상견과 착용 부위에 대해서

 - 대상견 : 5세, 요크셔테리어, 체고 30cm
 - 착용 부위 : 목 앞


## 4. Algorithm

### 4.1. Sampling / Preprocessing
기기는 초당 2회씩 3축 가속도 센서로부터 측정 가속도(Measured Acceleration)를 획득한다. 기기의 성능 한계로 인해 Serial 통신을 포함하는 코드는 2Hz이상 측정이 불가능하였다. 

측정 가속도(MA)는 움직임 성분(Linear Acclelration)과 중력 성분(Gravity Component)가 혼합된 값이다. 
측정값을 그대로 사용하는 것은 오차율을 높일 수 있기 때문에, Low Pass Filter를 사용해 반려견의 움직임(Body Component)과 중력 가속도(G)의 분리를 수행한다.

#### Low Pass Filter
저역 통과 필터는 낮은 주파수의 파동을 분리하는데 사용되며, 이 연구에서는 기기에 지속적으로 작용하는 중력가속을 분리하기 위해 사용되었다.
기기에 일정한 방향으로 작용하는 중력 가속은 일정하게 필터를 통과하게 되며, 이 값을 MA에서 제거함으로써 LA를 계산할 수 있다.

```
MA  = LA + G
G'  = Filter(MA, G)
    = a * MA + (1-a) * (G + E)
    = a * (LA + G) + (1-a) * G + E
    = a * LA + 1 * G + E
    = Previous G + Attenuated(약화) LA + Error
LA' = MA - G'
    = (1-a) * LA + E
```

정적인 자세(Static Posture)에서 필터링한 중력 가속도는 분산(Variance)이 적고, 그 크기(magnitude)가 1g(SI단위, 9.81 m/sec2)에 가속도 센서의 오차 내로 근사한다. 동적인 자세(Dynamic Posture)에서는 LA가 섞임에 따라 분산이 커지지만, 평균값은 정적인 자세와 거의 같다.

> #### How?
>  - Cutoff Frequency
>  - Alpha Optimization : `alpha = 0.7153`
>  - G, LA Description

### 4.2. Posture Classification

#### Posture Definition
분류대상이 되는 반려견의 자세는 다음과 같다.
정적일 때는 Lie(눕기), Sit/Stand(앉기/서있기)로 구분하며, 동적인 경우 Walk(걷기), Run(달리기)로 구분한다.
몸의 움직임 여부를 사용하는데 LA를, 몸의 기울기를 판단하는데는 G를 사용하였다.

#### Linear Acceleration
3축 가속도 센서로부터 획득한 X,Y,Z 성분은 벡터로 생각할 수 있다. 각 성분들은 기기에 작용하는 힘의 방향을 정규직교기저(Orthonormal Basis)로 표현한 것이며, 이때 LA는 반려견의 이동에 따른 가속도 벡터와 동일하다. 동시에 가속도와 비례하는 LA 벡터의 크기(norm)를 유도할 수 있다. 
하지만 LA는 Sample 단위로 획득하는 정보이며, 연속적인 움직임을 수치화하지 못한다. 가령 높은 Norm 값을 획득한 경우, 이것이 걸음걸이에 의한 충격인지 달리기에 의한 충격인지 모호하다. 

> LA and its Magnitude
```
LA   = {ax, ay, az}
Norm = sqrt(square(ax) + square(ay) + square(az))
```
> SMA Formula and Diagram

#### Signal Magnitude Area
LA를 누적시켜 반려견의 속도를 유도하기 위해, 제한된 크기의 Sliding Window를 사용하여 SMA(Signal Magnitude Area)를 계산한다.
Window 크기가 클수록 긴 시간동안의 움직임을 수치화 할 수 있으며, 반대로 계산을 위한 연산비용 역시 증가한다. 
이 구현에서는 제한된 메모리로 인해 약 2초간의 데이터(`T=4`)만을 유지하도록 하였다.

#### Naive Bayes

>  - Naive Bayes Description

Bounded memory usage, Simple implementation

Attribute들의 가중치(Weight)는 동일하게 고려하여 각 Posture와의 유사성(Similarity)을 계산한다.
이를 통해 매 Sample마다 가장 유사한 Posture를 추정할 수 있다.

>  - Naive Bayes for numeric type  
>    정규분포(평균,표준편차)에 근거한 Naive Bayes for numeric type의 구현.

| Posture | Ax        | Ay        | Az        | Norm      | SMA       |
|---------|-----------|-----------|-----------|-----------|-----------|
| Lie     | mean(dev) | mean(dev) | mean(dev) | mean(dev) | mean(dev) |
| SitSt   | mean(dev) | mean(dev) | mean(dev) | mean(dev) | mean(dev) |
| Walk    | mean(dev) | mean(dev) | mean(dev) | mean(dev) | mean(dev) |
| Run     | mean(dev) | mean(dev) | mean(dev) | mean(dev) | mean(dev) |


### 4.3. Orientation Inference
Posture Orientation은 몸의 기울기를 의미하며, 옆으로 누워 있거나(Lie-Side), 배를 하늘로 올리고 있는 경우(Lie-Back)를 알아내는데 필요하다.
정적인 자세에서 획득한 LA는 0 수렴하기 때문에 기기의 기울기를 파악할 수 없다. 또한 활동중인 경우 계속적인 움직임으로 인해 일정한 기울기를 계산하는 것은 매우 어렵다. 
착용부위가 고정적이라면 일정한 중력 방향이 존재함을 예상할 수 있으며, 일정시간 중력 가속도를 관찰하여 가속도계를 원점으로하는 평균적인 중력 벡터를 구할 수 있다. 이런 방식에서는 착용 부위가 변할 경우 새롭게 중력 평균을 계산해야한다.

정적인 자세에서(Stand) 평균 중력벡터(`Gavg`)를 계산해두면, 임의의 시점에 중력(`Gt`)과 끼인각을 계산할 수 있다. 중력벡터는 LA와 마찬가지로 X,Y,Z 성분으로 표현되할 수 있으므로, 끼인각의 계산은 3차원 벡터의 스칼라 곱(Scalar Product)을 계산하는 것과 동일하다. 이 방법은 정확한 몸의 기울기와 차이가 있을 수 있지만, 평균벡터를 사용하기 때문에 착용부위에 따라 유동적으로 적용이 가능하다는 장점을 가진다. 유도된 끼인각의 크기에 따라 곧음(Straight), 기욺(Lean), 뒤집힘(Reversed)로 구분할 수 있으며, Posture와 함께 적용하여 정적인 자세를 보다 정확히 파악할 수 있다. 

> 도식적 표현 필요함
```
Gavg= (Gx, Gy, Gz) // Averaged Gravity Acceleration
Gt = (Tx, Ty, Tz)   // Filtered Gravity Acceleration at Time `t`

Gavg' = Gavg / norm(Gavg)  // Normalization to unit vector
Gt' = Gt / norm(Gt)
dot = Gavg' * Gt'   // Dot(scala) product
theta = acos(dot); // Arc-cosine of product result
``` 

|         | Straight  | Lean       | Reversed  |
|---------|-----------|------------|-----------|
| Lie     | Lie       | Lie-Side   | Lie-Back  |
| SitSt   | SitSt     | SitSt-Side | Unknown   |
| Walk    | Walk      | Walk       | Unknown   |
| Run     | Run       | Run        | Unknown   |

## 5. Experiment
동작을 인식하는 알고리즘을 개발하기 위해 반려동물을 소형견, 중형견, 대형견으로 나누어 실제 데이터를 수집하고 이를 분류한다. 분류된 데이터의 검증을 위해 수 차례 반려동물과의 실험을 재 실시하여 행동 인식 기법을 개발한다.

또한 최대 진폭을 +-4g로 설정하였으며, Sampling Rate는 2Hz이다. 

### Protocol

### Result
수치 중심으로 실험 결과 서술. 
#### Expected Result
#### Actual Result

### Analysis
Classification Model의 정확도에 대한 분석


## 6. Discussion and Conclusion

### Discussion
시스템 전반에 대한 평가

 - 무게, 크기는 적합했는가? 
 - 배터리 소모량

### Conclusion

