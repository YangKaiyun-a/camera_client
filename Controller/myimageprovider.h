#ifndef MYIMAGEPROVIDER_H
#define MYIMAGEPROVIDER_H

#include <QQuickImageProvider>

class MyImageProvider : public QQuickImageProvider
{
public:
    static MyImageProvider *getInstance();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void setImage(const QImage &img);



private:
    MyImageProvider() : QQuickImageProvider(QQuickImageProvider::Image){}
    static MyImageProvider *m_myImageProvider;
    QImage m_image;
};

#endif // MYIMAGEPROVIDER_H
