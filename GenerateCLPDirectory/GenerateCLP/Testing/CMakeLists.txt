FIND_PACKAGE ( ITK )
IF ( ITK_FOUND )
  INCLUDE(${ITK_USE_FILE})
ELSE ( ITK_FOUND )
  MESSAGE ( FATAL_ERROR "Cannot build without ITK" )
ENDIF ( ITK_FOUND )

FIND_PACKAGE(GenerateCLP NO_MODULE REQUIRED)
IF(GenerateCLP_FOUND)
  INCLUDE(${GenerateCLP_USE_FILE})
ENDIF(GenerateCLP_FOUND)

SET ( CLPEXAMPLE1_SOURCE CLPExample1.cxx )
GENERATECLP(CLPEXAMPLE1_SOURCE CLPExample1.xml)
ADD_EXECUTABLE ( CLPExample1 ${CLPEXAMPLE1_SOURCE})
TARGET_LINK_LIBRARIES ( CLPExample1 ITKEXPAT)

SET ( POINTEXAMPLE1_SOURCE PointExample1.cxx )
GENERATECLP(POINTEXAMPLE1_SOURCE PointExample1.xml)
ADD_EXECUTABLE ( PointExample1 ${POINTEXAMPLE1_SOURCE})
TARGET_LINK_LIBRARIES ( PointExample1 ITKEXPAT)

SET ( SLICER3EXAMPLE_SOURCE Slicer3Example.cxx )
GENERATECLP(SLICER3EXAMPLE_SOURCE Slicer3Example.xml)
ADD_EXECUTABLE ( Slicer3Example ${SLICER3EXAMPLE_SOURCE})
TARGET_LINK_LIBRARIES ( Slicer3Example)

ADD_TEST(Slicer3CLPExample1 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example --help)
ADD_TEST(Slicer3CLPExample2 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example --echo --load_freesurfer_volume FSV --stereo)
ADD_TEST(Slicer3CLPExample3 ${EXECUTABLE_OUTPUT_PATH}/Slicer3Example)


