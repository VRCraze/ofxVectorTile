//
//  glmFeatureLabel.cpp
//  Labeling
//
//  Created by Patricio Gonzalez Vivo on 9/8/14.
//
//

#include "glmFeatureLabel.h"

glmFeatureLabel::glmFeatureLabel(): m_text("NONE"), m_alpha(0.0), m_cameraPos(NULL), bVisible(false), m_bChanged(true) {
    
}

glmFeatureLabel::glmFeatureLabel(const std::string &_text):m_text(_text), m_alpha(0.0), m_cameraPos(NULL), bVisible(false), m_bChanged(true){
    
}

glmFeatureLabel::~glmFeatureLabel(){
    FONScontext* ctx = m_font->getContext();
    glfonsUnbufferText(ctx, m_fsid);
};

std::string glmFeatureLabel::getText(){
    return m_text;
}

void glmFeatureLabel::setFont(glmFontRef &_fontRef){
    m_font = _fontRef;
    m_bChanged = true;
    
    if(m_font != NULL && m_font->isLoaded()) {
        FONScontext* ctx = m_font->getContext();
        glfonsBufferText(ctx, m_text.c_str(), &m_fsid);
    }
}

void glmFeatureLabel::setText(const std::string &_text){
    m_text = _text;
    stringPurifier(m_text);
    m_bChanged = true;
}

void glmFeatureLabel::setCameraPos(glm::vec3 *_camPos){
    m_cameraPos = _camPos;
}

unsigned int glmFeatureLabel::getId() const {
    return m_fsid;
}