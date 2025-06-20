#include "myimageprovider.h"

MyImageProvider* MyImageProvider::m_myImageProvider = nullptr;

MyImageProvider *MyImageProvider::getInstance()
{
    if(!m_myImageProvider)
    {
        m_myImageProvider = new MyImageProvider();
    }

    return m_myImageProvider;
}

QImage MyImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    if (size)
    {
        *size = m_image.size();
    }

    return m_image;
}

void MyImageProvider::setImage(const QImage &img)
{
    qDebug() << "接收到新图片" << img.size();
    // QString filename = QString("F:/pic_%1.jpg").arg(QDateTime::currentSecsSinceEpoch());
    // img.save(filename, "JPG");
    m_image = img;
}
