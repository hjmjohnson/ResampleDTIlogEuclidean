/*=========================================================================

  Program:   Diffusion Applications
  Module:    $HeadURL: http://svn.slicer.org/Slicer3/trunk/Applications/CLI/DiffusionApplications/ResampleDTI/itkDiffusionTensor3DInterpolateImageFunctionReimplementation.txx $
  Language:  C++
  Date:      $Date: 2010-04-29 11:58:49 -0400 (Thu, 29 Apr 2010) $
  Version:   $Revision: 13073 $

  Copyright (c) Brigham and Women's Hospital (BWH) All Rights Reserved.

  See License.txt or http://www.slicer.org/copyright/copyright.txt for details.

==========================================================================*/
#ifndef __DiffusionTensor3DInterpolateImageFunctionReimplementation_txx
#define __DiffusionTensor3DInterpolateImageFunctionReimplementation_txx

#include "itkDiffusionTensor3DInterpolateImageFunctionReimplementation.h"


namespace itk
{

template< class TData , class TCoordRep >
DiffusionTensor3DInterpolateImageFunctionReimplementation< TData , TCoordRep >
::DiffusionTensor3DInterpolateImageFunctionReimplementation()
{
  m_NumberOfThreads = 0 ;
}

template< class TData , class TCoordRep >
void
DiffusionTensor3DInterpolateImageFunctionReimplementation< TData , TCoordRep >
::SetInputImage( const DiffusionImageType *inputImage )
{
  DiffusionTensor3DInterpolateImageFunction< DataType >::SetInputImage( inputImage ) ;
  if( !inputImage )
  {
    return ;
  }
  typedef SeparateComponentsOfADiffusionTensorImage< TData , TData > SeparateType ;
  typename SeparateType::Pointer separateFilter = SeparateType::New() ;
  separateFilter->SetInput( inputImage ) ;
  separateFilter->SetNumberOfThreads( this->m_NumberOfThreads ) ;
  separateFilter->Update() ;
  AllocateInterpolator() ;
  for( int i = 0 ; i < 6 ; i++ )
  {
    m_Interpol[ i ]->SetInputImage( separateFilter->GetOutput( i ) ) ;
  }
}

template< class TData , class TCoordRep >
typename DiffusionTensor3DInterpolateImageFunctionReimplementation< TData , TCoordRep >
::TensorDataType 
DiffusionTensor3DInterpolateImageFunctionReimplementation< TData , TCoordRep >
::EvaluateAtContinuousIndex( const ContinuousIndexType & index ) const
{
  if( this->m_Image.IsNotNull() )//If input image has been set
  {
    TensorDataType pixelValue ;
    for( int i = 0 ; i < 6 ; i++ )
    {
      pixelValue[ i ] = ( DataType ) m_Interpol[ i ]->EvaluateAtContinuousIndex( index ) ;
    }
    return pixelValue ;
  }
  else
  {
    itkExceptionMacro( << "No InputImage Set" ) ;
  }  
}

}//end itk namespace

#endif
