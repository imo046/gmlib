
HEADERS +=

SOURCES +=

OTHER_FILES +=



# Module Headers
HEADERS_MODULES += \
    gmContainer \
    gmCore \
    gmDisplay \
    gmDisplayUtils \
    gmMisc \
    gmOpenGL \
    gmParametrics \
    gmUtils \
    gmVisualizers \


# C++ Headers
HEADERS_CPP += \
    gmAngle \
    gmArray \
    gmArrayLX \
    gmArrayT \
    gmArrow3D \
    gmCamera \
    gmCameraIso \
    gmCodeExample \
    gmColor \
    gmCoordinateSystem \
    gmDisplayObject \
    gmDMatrix \
    gmDVector \
    gmEvaluatorERBS \
    gmEvaluatorStatic \
    gmGLColor \
    gmGlobal \
    gmGLPhongShader \
    gmGLSL \
    gmLight \
    gmLightG \
    gmMaterial \
    gmMatrix \
    gmPApple \
    gmPArc \
    gmPAsteroidalSphere \
    gmPathTrack \
    gmPBezierCurve \
    gmPBezierSurf \
    gmPBSplineCurve \
    gmPButterfly \
    gmPChrysanthemumCurve \
    gmPCircle \
    gmPCircularSurface \
    gmPCurve \
    gmPCylinder \
    gmPERBSCurve \
    gmPERBSSurf \
    gmPLuaScriptCurve \
    gmPLuaScriptSurf \
    gmPoint \
    gmPoint2D \
    gmPoint3D \
    gmPPlane \
    gmPRoseCurve \
    gmPSphere \
    gmPSteinerSurf \
    gmPSurf \
    gmPTCurve \
    gmPTorus \
    gmRandom \
    gmSArray \
    gmScene \
    gmSceneObject \
    gmScript \
    gmSelector \
    gmSelectorGrid \
    gmSimplex \
    gmSphere3D \
    gmStaticProc \
    gmStaticProc2 \
    gmStlObject \
    gmStream \
    gmString \
    gmSubSpace \
    gmSurroundingSphere \
    gmTexture \
    gmTimer \
    gmTriangleSystem \
    gmVContours \
    gmVDefault \
    gmVDerivatives \
    gmVDynamicTexture \
    gmVDynamicTextureAnimation \
    gmVGLContoursPhongShader \
    gmVGLPhongShader \
    gmVGLShader \
    gmVisualizer \
    gmVNormals \
    gmVPoints \
    gmWindow




#########
# Headers

HEADERS += \
    gmAngle.h \
    gmArray.h \
    gmArrayLX.h \
    gmArrayT.h \
    gmArrow3D.h \
    gmCamera.h \
    gmCameraIso.h \
    gmCodeExample.h \
    gmColor.h \
    gmCoordinateSystem.h \
    gmDisplayObject.h \
    gmDMatrix.h \
    gmDVector.h \
    gmEvaluatorERBS.h \
    gmEvaluatorStatic.h \
    gmGLColor.h \
    gmGlobal.h \
    gmGLPhongShader.h \
    gmGLSL.h \
    gmLight.h \
    gmLightG.h \
    gmMaterial.h \
    gmMatrix.h \
    gmOpenGL.h \
    gmPApple.h \
    gmParametrics.h \
    gmPArc.h \
    gmPAsteroidalSphere.h \
    gmPathTrack.h \
    gmPBezierCurve.h \
    gmPBezierSurf.h \
    gmPBSplineCurve.h \
    gmPButterfly.h \
    gmPChrysanthemumCurve.h \
    gmPCircle.h \
    gmPCircularSurface.h \
    gmPCurve.h \
    gmPCylinder.h \
    gmPERBSCurve.h \
    gmPERBSSurf.h \
    gmPLuaScriptCurve.h \
    gmPLuaScriptSurf.h \
    gmPoint.h \
    gmPoint2D.h \
    gmPoint3D.h \
    gmPPlane.h \
    gmPRoseCurve.h \
    gmPSphere.h \
    gmPSteinerSurf.h \
    gmPSurf.h \
    gmPTCurve.h \
    gmPTorus.h \
    gmRandom.h \
    gmSArray.h \
    gmScene.h \
    gmSceneObject.h \
    gmScript.h \
    gmSelector.h \
    gmSelectorGrid.h \
    gmSimplex.h \
    gmSortObject.h \
    gmSphere3D.h \
    gmStaticProc.h \
    gmStaticProc2.h \
    gmStlObject.h \
    gmStream.h \
    gmString.h \
    gmSubSpace.h \
    gmSurroundingSphere.h \
    gmTexture.h \
    gmTimer.h \
    gmTriangleSystem.h \
    gmVContours.h \
    gmVDefault.h \
    gmVDerivatives.h \
    gmVDynamicTexture.h \
    gmVDynamicTextureAnimation.h \
    gmVGLContoursPhongShader.h \
    gmVGLPhongShader.h \
    gmVGLShader.h \
    gmVisualizer.h \
    gmVNormals.h \
    gmVPoints.h \
    gmWindow.h \
    gmUtils.h


#########
# Sources

SOURCES += \
    gmCamera.cpp \
    gmCameraIso.cpp \
    gmCodeExample.cpp \
    gmColor.cpp \
    gmCoordinateSystem.cpp \
    gmDisplayObject.cpp \
    gmGLSL.cpp \
    gmGLPhongShader.cpp \
    gmLight_Light.cpp \
    gmLight_PointLight.cpp \
    gmLight_SpotLight.cpp \
    gmLight_Sun.cpp \
    gmLightG_PointLightG.cpp \
    gmLightG_SpotLightG.cpp \
    gmMaterial_Material.cpp \
    gmMaterial_MaterialObjectList.cpp \
    gmOpenGL_GLMatrix.cpp \
    gmPathTrack.cpp \
    gmScene.cpp \
    gmSceneObject.cpp \
    gmScript_LuaScript.cpp \
    gmScript_LuaVar.cpp \
    gmScript_Script.cpp \
    gmStlObject.cpp \
    gmStream_Separator.cpp \
    gmSurroundingSphere.cpp \
    gmTexture.cpp \
    gmWindow_GMWindow.cpp \
    gmWindow_View.cpp \
    gmWindow_ViewSet.cpp

##################
# Template sources

SOURCES_TEMPLATES += \
    gmPBSplineSurf.c \
    gmCameraIso.c \
    gmCamera.c \
    gmArrow3D.c \
    gmArrayT.c \
    gmArrayLX.c \
    gmArray.c \
    gmAngle.c \
    gmTimer.c \
    gmSubSpace_SubSpace.c \
    gmSubSpace_Plane.c \
    gmSubSpace_Line.c \
    gmSubSpace_Cube.c \
    gmString.c \
    gmStream_Separator.c \
    gmStlObject.c \
    gmStaticProc_GM_Std_.c \
    gmStaticProc_GM_Static_.c \
    gmStaticProc_GM_Static3_.c \
    gmStaticProc_GM_Static2_.c \
    gmStaticProc_GM_Static1_.c \
    gmStaticProc2_GM_Static_P_.c \
    gmStaticProc2_GM_Static_P2_.c \
    gmSphere3D.c \
    gmSimplex_Triangle.c \
    gmSimplex_Tetrahedron.c \
    gmSimplex_Simplex.c \
    gmSimplex_LineSegment.c \
    gmSelectorGrid.c \
    gmSelector.c \
    gmSceneObject.c \
    gmScene.c \
    gmSArray.c \
    gmRandom.c \
    gmPTorus.c \
    gmPTCurve.c \
    gmPSurf.c \
    gmPSteinerSurf.c \
    gmPSphere.c \
    gmPRoseCurve.c \
    gmPPlane.c \
    gmPoint_Vector.c \
    gmPoint_UnitVector.c \
    gmPoint_Sphere.c \
    gmPoint_ScalarPoint.c \
    gmPoint_Point.c \
    gmPoint_M_I_.c \
    gmPoint_Box.c \
    gmPoint_Arrow.c \
    gmPoint3D_Vector3D.c \
    gmPoint3D_UnitVector3D.c \
    gmPoint3D_Point3D.c \
    gmPoint3D_Plane3D.c \
    gmPoint2D_Vector2D.c \
    gmPoint2D_UnitVector2D.c \
    gmPoint2D_Point2D.c \
    gmPLuaScriptSurf.c \
    gmPLuaScriptCurve.c \
    gmPERBSSurf.c \
    gmPERBSCurve.c \
    gmPCylinder.c \
    gmPCurve.c \
    gmPCircle.c \
    gmPButterfly.c \
    gmPBSplineCurve.c \
    gmPBezierSurf.c \
    gmPBezierCurve.c \
    gmPArc.c \
    gmParametrics.c \
    gmPApple.c \
    gmOpenGL_ScaleObj.c \
    gmOpenGL_GLMatrix.c \
    gmOpenGL_Frustum.c \
    gmOpenGL.c \
    gmMatrix_SqMatrix.c \
    gmMatrix_Matrix.c \
    gmMatrix_HqMatrix.c \
    gmMaterial_MaterialObjectList.c \
    gmMaterial_MaterialObject.c \
    gmMaterial_Material.c \
    gmLight_Sun.c \
    gmLight_SpotLight.c \
    gmLight_PointLight.c \
    gmLight_Light.c \
    gmGLColor.c \
    gmEvaluatorStatic.c \
    gmEvaluatorERBS.c \
    gmDVector.c \
    gmDMatrix.c \
    gmDisplayObject.c \
    gmColor.c \
    gmWindow_ViewSet.c \
    gmWindow_ViewBorder.c \
    gmWindow_View.c \
    gmWindow_GMWindow.c \
    gmVPoints.c \
    gmVNormals.c \
    gmVisualizer.c \
    gmVGLShader.c \
    gmVGLPhongShader.c \
    gmVGLContoursPhongShader.c \
    gmVDynamicTextureAnimation.c \
    gmVDynamicTexture.c \
    gmVDerivatives.c \
    gmVDefault.c \
    gmVContours.c \
    gmPChrysanthemumCurve.c \
    gmPAsteroidalSphere.c \
    gmTriangleSystem_TSVertex.c \
    gmTriangleSystem_TSTriangle.c \
    gmTriangleSystem_TSTile.c \
    gmTriangleSystem_TSLine.c \
    gmTriangleSystem_TSEdge.c \
    gmTriangleSystem_TriangleSystem.c \
    gmTriangleSystem_TriangleFacets.c \
    gmSortObject.c \
    gmPCircularSurface.c \
    gmUtils.c

SOURCES_LUA += \
    lua/pcircle_eval.lua \
    lua/psphere_eval.lua \

SOURCES_GLSL +=



OTHER_FILES += \ $$HEADERS_MODULES $$HEADERS_CPP $$SOURCES_TEMPLATES $$SOURCES_LUA

include( ../gmlib.pri )

TARGET = gmlib

include( ../gmlib_cpp.pri )
