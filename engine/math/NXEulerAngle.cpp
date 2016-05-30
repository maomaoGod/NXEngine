/*
 *  File:    NXEulerAngle.cpp
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 欧拉角操作函数
 */
#include "NXEulerAngle.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXQuaternion.h"
#include "NXAlgorithm.h"

namespace NX {
    EulerAngle::EulerAngle(){
        heading = pitch = bank = 0.0f;
    }
    
    EulerAngle::EulerAngle(const EulerAngle &rhs){
        heading  = rhs.heading;
        pitch    = rhs.pitch;
        bank     = rhs.bank;
    }

    EulerAngle::EulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode):EulerAngle(MatrixToEulerAngle(rhs, mode)){
        
    }

    EulerAngle::EulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode):EulerAngle(MatrixToEulerAngle(rhs, mode)){
        
    }

    EulerAngle::EulerAngle(const float yAxisRotateAngle, const float xAxisRotateAngle, const float zAxisRotateAngle){
        heading = yAxisRotateAngle;
        pitch   = xAxisRotateAngle;
        bank    = zAxisRotateAngle;
    }

    EulerAngle::~EulerAngle(){
        //empty here
    }
    
    EulerAngle& EulerAngle::Normalize(){
        pitch    = DG2RD(pitch);
        heading  = DG2RD(heading);
        bank     = DG2RD(bank);
        pitch += kfPi;
        Wrap(pitch, kfPi);
        if(pitch < -kfPiOver2){
            pitch     = -kfPi - pitch;
            heading  += kfPi;
            bank     += kfPi;
        }else if(pitch > kfPiOver2){
            pitch     = kfPi - pitch;
            heading  += kfPi;
            bank     += kfPi;
        }else{
            //nothing
        }
        if(NXAbs(pitch) > kfPiOver2 - Epsilon<float>::m_Epsilon){
            heading += bank;
            bank     = 0.0f;
        }else{
            Wrap(bank, kfPi);
        }
        Wrap(heading, kfPi);
        pitch    = RD2DG(pitch);
        heading  = RD2DG(heading);
        bank     = RD2DG(bank);
        return *this;
    }
    
    EulerAngle EulerAngle::GetNormalized() const{
        return EulerAngle(*this).Normalize();
    }
    
    const EulerAngle kEulerAngleIndentity(0.0f, 0.0f, 0.0f);
}