/****************************************************************************
**
** Copyright (C) 2017 Vikas Thamizharasan.

****************************************************************************/

#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <QtCore/qmath.h>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>

#include <Qt3DInput/QKeyboardHandler>

#include <Qt3DRender/QMesh>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>


#include <QDialogButtonBox>
#include <QFormLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>

class SceneModifier : public QObject
{
    Q_OBJECT

public:
    explicit SceneModifier(Qt3DCore::QEntity *rootEntity, QWidget *parentWidget);
    ~SceneModifier();

    QList<QVector3D>* vertices;
    QList<QVector2D>* lineRawData;
    QList<QList<int>> facelineRawData;
    QList<QList<int>> facelpointRawData;
    QList<QVector3D>* cylinder;
    QList<QVector4D>* circle;

    QList<QString>* line_param;
    QList<QString>* faceline_param;
    QList<QString>* facepoint_param;
    QList<QString>* cylinder_param;
    QList<QString>* circle_param;

public slots:
    void enableCaoMesh(bool enabled);
    void mouseControls(Qt3DInput::QKeyEvent *event);
    void parse3DFile(QTextStream &input);

private slots:
    void handlePickerPress(Qt3DRender::QPickEvent *event);
    void createCylinder(QVector3D axis_1, QVector3D axis_2,
                        unsigned int index, float radius, QString load_param);
    void createCircle(QVector3D circum_1, QVector3D circum_2, QVector3D center,
                      unsigned int index, float radius, QString load_param);
    void createLines(QVector3D v0, QVector3D v1,
                     const unsigned int index, const bool axis, QString lod_param);
    int primitiveType(const QString &type);
    QString getLodParameters(QStringList data,
                          const unsigned int idx1, const unsigned int idx2);

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_caoEntity;
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QEntity *m_cylinderEntity;
    Qt3DCore::QEntity *m_circleEntity;
    QWidget *m_parentWidget;

    //QList<Qt3DRender::QObjectPicker *> *m_facePickers;
    Qt3DExtras::QPhongMaterial *caoMaterial;

};

#endif // SCENEMODIFIER_H
