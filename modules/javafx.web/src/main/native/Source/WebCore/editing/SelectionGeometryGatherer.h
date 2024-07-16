/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(SERVICE_CONTROLS)

#include <wtf/CheckedRef.h>
#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>
#include <wtf/WeakRef.h>

namespace WebCore {

class FloatQuad;
class LayoutRect;
class RenderLayerModelObject;
class RenderView;

struct GapRects;

class SelectionGeometryGatherer {
    WTF_MAKE_NONCOPYABLE(SelectionGeometryGatherer);

public:
    SelectionGeometryGatherer(RenderView&);

    void addQuad(const RenderLayerModelObject* repaintContainer, const FloatQuad&);
    void addGapRects(const RenderLayerModelObject* repaintContainer, const GapRects&);
    void setTextOnly(bool isTextOnly) { m_isTextOnly = isTextOnly; }
    bool isTextOnly() const { return m_isTextOnly; }

    class Notifier {
        WTF_MAKE_FAST_ALLOCATED;
        WTF_MAKE_NONCOPYABLE(Notifier);
    public:
        Notifier(SelectionGeometryGatherer&);
        ~Notifier();

    private:
        SelectionGeometryGatherer& m_gatherer;
    };

    std::unique_ptr<Notifier> clearAndCreateNotifier();

private:
    Vector<LayoutRect> boundingRects() const;

    SingleThreadWeakRef<RenderView> m_renderView;

    // All rects are in RenderView coordinates.
    Vector<FloatQuad> m_quads;
    Vector<GapRects> m_gapRects;
    bool m_isTextOnly;
};

} // namespace WebCore

#endif // ENABLE(SERVICE_CONTROLS)
