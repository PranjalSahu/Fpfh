/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkMyFilter_h
#define itkMyFilter_h

#include "itkPointsLocator.h"
#include "itkMeshToMeshFilter.h"

namespace itk
{

/** \class MyFilter
 *
 * \brief Filters a image by iterating over its pixels.
 *
 * Filters a image by iterating over its pixels in a multi-threaded way
 * and {to be completed by the developer}.
 *
 * \ingroup Fpfh
 *
 */
template <typename TInputPointSet, typename TOutputPointSet>
class MyFilter : public itk::MeshToMeshFilter<TInputPointSet, TOutputPointSet>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MyFilter);

  static constexpr unsigned int InputDimension = TInputPointSet::PointDimension;
  static constexpr unsigned int OutputDimension = TOutputPointSet::PointDimension;

  using InputPointSetType = TInputPointSet;
  using OutputPointSetType = TOutputPointSet;
  using InputPixelType = typename InputPointSetType::PixelType;
  using OutputPixelType = typename OutputPointSetType::PixelType;

  /** Standard class aliases. */
  using Self = MyFilter<InputPointSetType, OutputPointSetType>;
  using Superclass = MeshToMeshFilter<InputPointSetType, OutputPointSetType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  using PointType = typename TInputPointSet::PointType;
  using PointIdentifier = typename TInputPointSet::PointIdentifier;
  using PointsVectorContainer = typename TInputPointSet::PointsVectorContainer;

  using InputPointSetPointsContainerConstPointer = typename TInputPointSet::PointsContainerConstPointer;
  using PointsContainerConstIterator = typename InputPointSetType::PointsContainer::ConstIterator;
  using Vector3d = typename itk::Vector<double, 3>;
  using Vector4d = typename itk::Vector<double, 4>;

  using PointsLocatorType = typename itk::PointsLocator<itk::VectorContainer<PointIdentifier, PointType>>;
  using PointsLocatorTypePointer = typename PointsLocatorType::Pointer;
  //using FeatureType = std::vector<double>;
  using FeatureType = typename itk::VectorContainer<PointIdentifier, double>;

  /** Run-time type information. */
  itkTypeMacro(MyFilter, MeshToMeshFilter);

  /** Standard New macro. */
  itkNewMacro(Self);

  FeatureType * ComputeSPFHFeature(
        InputPointSetType * input,
        InputPointSetType * input_normals,
        unsigned int radius,
        unsigned int neighbors);
  
  FeatureType * ComputeFPFHFeature(
        InputPointSetType * input,
        InputPointSetType * input_normals,
        unsigned int radius,
        unsigned int neighbors);

protected:
  MyFilter();
  ~MyFilter() override = default;

  void
  GenerateData() override;

  Vector4d ComputePairFeatures(const Vector3d &p1,
                                           const Vector3d &n1,
                                           const Vector3d &p2,
                                           const Vector3d &n2);

  
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
#ifdef ITK_USE_CONCEPT_CHECKING
  // Add concept checking such as
  // itkConceptMacro( FloatingPointPixel, ( itk::Concept::IsFloatingPoint< typename InputImageType::PixelType > ) );
#endif
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkMyFilter.hxx"
#endif

#endif // itkMyFilter
