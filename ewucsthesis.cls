\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ewucsthesis}[2014/03/14 - Thesis formatting for the EWU library]

\PassOptionsToClass{titlepage}{article}
\LoadClassWithOptions{article}

\usepackage[top=1in, bottom=1in, left=1.5in, right=1in]{geometry}

\let\@primaryadviser\relax
\def\primaryadviser#1{\def\@primaryadviser{#1}}

\let\@secondaryadviser\relax
\def\secondaryadviser#1{\def\@secondaryadviser{#1}}

\newcommand{\tallhrule}{\vspace{1.5cm}\hrule\vspace{1.5cm}}


\newcommand*{\SignatureAndDate}[1]{
    \small
    \par\noindent\makebox[4.2in]{\hrulefill} \hfill\makebox[1.3in]{\hrulefill}
    \par\noindent\makebox[4.1in][l]{#1}      \hfill\makebox[1.1in][l]{DATE}
}

\renewcommand{\maketitle}{
\begin{titlepage}
\pagenumbering{roman}
\makeatletter
\begin{center}
\begin{doublespacing}
 \textsc{\LARGE \@title}
 \tallhrule
 \Large
 A Thesis\\
 Presented To\\
 Eastern Washington University\\
 Cheney, Washington
 \tallhrule
 In Partial Fulfillment of the Requirements\\
 for the Degree\\
 Master of Science in Computer Science
 \tallhrule
 By\\
 \@author\\
 \@date
 \clearpage

 % Committee signature
 \vspace*{\fill}
 \textsc{Thesis of \@author~Approved by}
 \vspace{3in}
 \SignatureAndDate{\MakeUppercase{\@primaryadviser}, GRADUATE STUDY COMMITTEE}
 \vspace{1in}
 \SignatureAndDate{\MakeUppercase{\@secondaryadviser}, GRADUATE STUDY COMMITTEE}
 \vspace*{\fill}
 \clearpage
\end{doublespacing}

 % Authorization/copyright
 \vspace*{\fill}
 \textsc{\Large \underline{Master's Thesis}}\\
 \vspace{\fill}
\end{center}
 \normalsize
 In presenting this thesis in partial fulfillment of the requirements for a master’s
 degree at Eastern Washington University, I agree that the JFK Library shall make
 copies freely available for inspection. I further agree that copying of this project
 in whole or in part is allowable only for scholarly purposes. It is understood,
 however, that any copying or publication of this thesis for commercial purposes,
 or for financial gain, shall not be allowed without my written permission.
 \vspace{\fill}
 \SignatureAndDate{SIGNATURE}
 \vspace*{\fill}
 \clearpage

 % Table of Contents
 \normalsize
 \tableofcontents
 \listoffigures
%  \listoftables
\clearpage
\end{titlepage}
\pagenumbering{arabic}
\thispagestyle{empty}
}
