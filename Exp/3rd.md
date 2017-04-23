# 3차 실험 결과보고

#### 실험 목표
반려견이 착용한 IMU 센서 값을 수집하여 추가적인 값들을 유도하고, 그 양상을 분석한다.

#### 실험 결과
 1. 정적인 상태와 동적인 상태가 그래프 상으로 명확히 구분이 가능하였다.
 1. 안정적인 경우는 중력 축과의 각도를 확인할 수 있었지만, 지표의 유용성은 확신할 수 없었다.
 1. 향후 통계적인 방향으로 접근할 수 있으므로 같은 조건에 대해 약 3회정도 더 데이터를 수집할 필요가 있다.
   - Lying, Running 상태를 추가하여 값을 비교한다.

## 실험 내용
 - 실험일 : 2017/02/09 저녁
 - 실험 진행 : 박동하(luncliff@gmail.com)

### 실험 대상

![Fig1착용](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/20170209_193612.jpg)

 - 견종 : 요크셔테리어
 - 나이 : 5년
 - 체고 : 약 30cm
 - 신장 : 약 48cm
 - 체중 : 4.7kg

### 실험 구성
실험은 Sitting 상태와 Walking 상태를 각 2회씩 측정한다. 

각각의 가속도 축은 강아지 자신을 기준으로 다음과 같은 방향에 위치하도록 센서를 착용하였다. 

 - +Z (바닥), -Z (천장)
 - +Y (앞쪽), -Y (뒤쪽)
 - +X (오른쪽), -X (왼쪽)
 - 자이로의 축은 별도로 조정하지 않음.

따라서, 일반적인 정면 보행의 경우 +Z, +Y가 조합되며, 몸이 옆으로 기울게 되면 가속도 X축 상에서 그 변화를 감지할 수 있도록 하였다. 


### 기대 결과
 1. 1차, 2차 실험결과를 바탕으로 할 때, 정적/동적 상태일 때 **SMV** (Signal Magnitude Vector), **SMA** (Signal Magnitude Area) 값이 명확히 구분 가능할 것으로 생각된다.   
 1. 추가적으로 중력 가속도를 기반으로 한 **중력 축과의 각도**를 유도하여, 실제와 부합하는지를 비교해본다.


## 실험 결과

### 결과 데이터
 - **[Excel Chart](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/3rdData.xlsx)**
 - [Sit 1](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/sit1.out.txt)
 - [Sit 2](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/sit2.out.txt)
 - [Walk 1](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/walk1.out.txt)
 - [Walk 2](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/walk2.out.txt)

### 결과 분석
종종 센서값의 잘못된 처리로 예상되는 값들이 확인된다. 이는 여러차례 실험을 통해 적합한 값의 범위를 추정하고, 그에 맞게 필터링을 하도록 조정해야 할 것으로 보인다.

>
> 박동하 : 값의 범위는 따로 통계를 내봐야 할 것 같습니다. 이전 회의 내용대로 실험 횟수를 좀 더 늘리도록 하겠습니다. 다른 반려견을 대상으로도 데이터를 수집할 수 있도록 할 방법이 필요할 것 같습니다.
> 

#### Sitting
1차, 2차 실험결과와 마찬가지로 거의 변화가 없다.

| Acc   | Gyro
| ----- | --- 
| ![Fig2a_Acc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.Acc.jpg) | ![Fig2b_Gyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.Gyro.jpg)

#### Walking
 - 가속도 X축 : 걷고 있는 경우 강아지 몸의 좌우 흔들림에 의해서 값이 변화하는 것을 확인할 수 있다.
 - 가속도 Y축 : 값의 범위는 0.6 부근으로 앉아있을 때에 비해서 좀 더 많은 변화가 관찰된다.
 - 가속도 Z축 : 바닥을 향하는 중력과 일치하는 Z축은 상대적으로 일정한 값이 유지되는 것을 확인할 수 있다.

 - 자이로 : 값이 주기적인 양상을 보인다.

| Acc   | Gyro
| ----- | --- 
| ![Fig3a_Acc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.Acc.jpg) | ![Fig3b_Gyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.Gyro.jpg)


#### SMV

`Sitting` 때의 Signal Magnitude Vector는 대부분 1에 근접한데 반해, `Walking`상태에서는 0에 근접한 결과가 빈번하게 관측된다. 

이는 가속도(Acc) 값이 보통 [0,1] 범위에 속하기 때문에, `square`처리를 수행하면서 0에 근사하게 되기 때문이라 추정된다.

반면 각속도(Gyro)는 [0,300] 범위 내에서 변화를 보다 분명하게 확인할 수 있었다. 

>
> 박동하 : 일정 크기의 Window로 EWMA를 계산할 수 있을 것으로 보입니다
>


| Sitting   | Walking
| -----     | -----
| ![Fig4a_Sit_SMVAcc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.SMVAcc.jpg) | ![Fig4b_Walk_SMVAcc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.SMVAcc.jpg)
| ![Fig5a_Sit_SMVGyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.SMVGyro.jpg) | ![Fig5b_Walk_SMVGyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.SMVGyro.jpg)


#### SMA 30
이전의 측정 결과 30개를 사용해 Signal Magnitude Area를 계산한 결과. 튀는 값에 의해서 계산 결과가 그게 변하는 것을 확인할 수 있었다. 보다 유의미한 형태가 되기 위해선 필터링을 우선 적용해야 할 것으로 보인다.


| Sitting   | Walking
| -----     | -----
| ![Fig6a_Sit_SMAAcc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.SMAAcc.jpg) | ![Fig6b_Walk_SMAAcc](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.SMAAcc.jpg)
| ![Fig6a_Sit_SMAGyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.SMAGyro.jpg) | ![Fig6b_Walk_SMAGyro](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.SMAGyro.jpg)


#### Tilt

강아지가 엉덩이를 내리고 앉아있을 떄는 약 30~40도 정도의 기울기를 관찰할 수 있었다. 반면 보행중에는 이 값이 매우 크게 변화하며, 80도 이상의 기울기가 관측되기도 하였다.

착용 형태를 고려할때 70도 이상의 값은 옷의 흔들림에 의한 오차가 있을 것으로 추정된다.


| Sitting   | Walking
| -----     | -----
| ![Fig7a_Tilt_Sit](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Sit1.Tilt.jpg) | ![Fig7b_Tilt_Walk](https://github.com/OliveOld/Documents/blob/master/Experiment/3rd/Images/Walk1.Tilt.jpg)


## 결론
 1. 정적인 상태와 동적인 상태가 그래프 상으로 명확히 구분이 가능하였다.
 1. 안정적인 경우는 중력 축과의 각도를 확인할 수 있었지만, 지표의 유용성은 확신할 수 없었다.
 1. 향후 통계적인 방향으로 접근할 수 있으므로 같은 조건에 대해 약 3회정도 더 데이터를 수집할 필요가 있다.
   - Lying, Running 상태를 추가하여 값을 비교한다.

