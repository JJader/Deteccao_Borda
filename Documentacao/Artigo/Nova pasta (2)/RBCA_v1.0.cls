%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RBCA.cls, v1.0, 2017/08/15
% Developed by Carlos Amaral Hölbig
% 
% This class file enables authors to prepare 
% manuscripts for submission to RBCA journal
%
% V1.0 
% - new version of latex template for RBCA papers
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
\ProvidesClass{RBCA_v1.0}[2017/08/15, v1.0]

\newif\if@numrefs
\newif\if@alpharefs

%% Options for bibliography style
\DeclareOption{num-refs}{
  \@numrefstrue
  \@alpharefsfalse
}
\DeclareOption{alpha-refs}{
  \@numrefsfalse
  \@alpharefstrue
}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}

\ExecuteOptions{num-refs}
\ProcessOptions\relax
\LoadClass[twoside,twocolumn]{article}

\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage{microtype}
\RequirePackage{merriweather}
\renewcommand{\ttdefault}{lmtt}
\RequirePackage[italic]{mathastext}
\RequirePackage{relsize}
\RequirePackage{ragged2e}
\RequirePackage{xcolor}
\RequirePackage{colortbl}
\RequirePackage{graphicx}
\RequirePackage{etoolbox,xpatch}
\RequirePackage{environ}
\RequirePackage{lastpage}
\RequirePackage{rotating}
\RequirePackage{lscape}
\RequirePackage{afterpage}
\RequirePackage[absolute]{textpos}
\RequirePackage{url}
\RequirePackage{newfloat}
\RequirePackage{mdframed}
\RequirePackage{titlesec}
\RequirePackage{setspace}
\RequirePackage{threeparttable}
\RequirePackage{epstopdf}
\RequirePackage{siunitx}
\RequirePackage{amsmath}

\RequirePackage{listings}
\lstset{numbers=left, 
xleftmargin=2em,
framexleftmargin=1.5em,
frame=single,
numbersep=5pt, 
backgroundcolor=\color{gray!10},
commentstyle=\scriptsize\color{blue},
basicstyle=\scriptsize} 

\RequirePackage{scrextend}
\changefontsizes[10.5pt]{9pt}

\RequirePackage{calc}
\RequirePackage{geometry}
\geometry{includefoot,
  hmargin=4pc+6.64pt,
  bottom=2pc+6pt,
  top=6pc+6pt,
  headsep=2pc,
  headheight=17.5pt,
  footnotesep=1pc+6pt,
  columnsep=18pt}
\setlength{\parindent}{12pt}

\RequirePackage[flushmargin,bottom]{footmisc}

\RequirePackage[colorlinks,bookmarksopen,bookmarksnumbered,citecolor=blue,urlcolor=blue, linkcolor=blue]{hyperref}

\RequirePackage[noblocks]{authblk}

% Editora UPF logo file
\def\@upflogo{editora_logo.png}

\newcommand{\jname}[1]{\def\@jname{#1}}
\newcommand{\jlogo}[1]{\def\@jlogo{#1}}

\def\@jyear{}
\def\@jvolume{}
\def\@jissue{}
\def\@jmonth{}

\def\@jpages{}
\def\@jid{}

\def\@jrec{}
\def\@jrev{}
\def\@jacc{}

\newcommand{\jyear}[1]{\def\@jyear{#1}}
\newcommand{\jvolume}[1]{\def\@jvolume{#1}}
\newcommand{\jissue}[1]{\def\@jissue{#1}}
\newcommand{\jmonth}[1]{\def\@jmonth{#1}}
\newcommand{\jid}[1]{\def\@jid{#1}}

\def\@shortDOI{10.5335/rbca.v\@jvolume i\@jissue .\@jid}
\newcommand{\shortDOI}[1]{\def\@shortDOI{#1}}
\newcommand{\jpages}[1]{\def\@jpages{#1}}

\newcommand{\jrec}[1]{\def\@jrec{#1}}
\newcommand{\jrev}[1]{\def\@jrev{#1}}
\newcommand{\jacc}[1]{\def\@jacc{#1}}

\def\@papercat{}
\def\@runningauthor{}
\def\@runningtitle{}
\def\@corraddress{}
\def\@authnotes{}

\newcommand{\runningauthor}[1]{\def\@runningauthor{#1}}
\newcommand{\runningtitle}[1]{\def\@runningtitle{#1}}
\newcommand{\corraddress}[1]{\def\@corraddress{#1}}
\newcommand{\authnote}[1]{\appto{\@authnotes}{#1\par}}
\newcommand{\papercat}[1]{\def\@papercat{#1}}

\jname{Revista Brasileira de Computação Aplicada}%
\jlogo{rbca_logo.png}%
\definecolor{jcolour}{RGB}{0,100,0}%

\RequirePackage{fancyhdr}
\fancyhf{}
\renewcommand{\headrule}{\color{jcolour}\rule{\textwidth}{2pt}}
\fancyhead[LE]{%
  \hspace*{12pt}%
  \fontsize{9pt}{10pt}\selectfont%
  \color{jcolour}%
  \textbf{\thepage}%
  \hspace{1em}\raisebox{-0.5pt}{|}\hspace{1em}%
  \@runningauthor / \textit{\@jname}~(\@jyear), v.\@jvolume, n.\@jissue, pp.\@jpages%
}
\fancyhead[RO]{%
  \fontsize{9pt}{10pt}\selectfont%
  \color{jcolour}%
  \@runningauthor / \textit{\@jname}~(\@jyear), v.\@jvolume, n.\@jissue, pp.\@jpages%
  \hspace{1em}\raisebox{-0.5pt}{|}\hspace{1em}%
  \textbf{\thepage}%
  \hspace*{12pt}%
}

\fancypagestyle{plain}{%
  \fancyhf{}
  \renewcommand{\headrule}{}
  \fancyfoot[R]{%
    \fontsize{9pt}{10pt}\selectfont%
    \color{jcolour}%
    \textbf{\thepage}\hspace*{12pt}%
  }
}


\pagestyle{fancy}


\AtBeginDocument{%
  \newsavebox{\@gscitedetails}
  \newlength{\@gscitedetailsheight}
  \newsavebox{\@gsheadbox}
  \newlength{\@gsheadboxheight}
  \savebox{\@gscitedetails}{%
    \parbox{\textwidth-21pc+4pc+6.64pt}{%
    {\color{jcolour}\rule{\linewidth-2cm}{2pt}}\par%
    \vspace{\dimexpr 10pt-1em\relax}%
    \fontsize{8pt}{9.5pt}\bfseries%
    DOI: \href{http://dx.doi.org/\@shortDOI}{\@shortDOI}\par
    Vol.~\@jvolume, N$^{\underline{o}}$~\@jissue, pp.~\@jpages \par
    Homepage: \href{http://seer.upf.br/index.php/rbca/index}{seer.upf.br/index.php/rbca/index}\par
    \vspace{\dimexpr 8pt-1em\relax}%
    {\color{jcolour}\rule{\linewidth-2cm}{2pt}}\par
  }}%
  \settototalheight{\@gscitedetailsheight}{\usebox{\@gscitedetails}}%
  %%%%
  \savebox{\@gsheadbox}{%
    \parbox{\textwidth-21pc+4pc+6.64pt}{%
    \normalfont%
    \fontsize{7.5pt}{9.5pt}\selectfont%
    {\bfseries\@jname, \@jmonth, \@jyear}\par
    \vspace{\dimexpr 4pt-1.5pt\relax}%
    \usebox{\@gscitedetails}
    }%
  }%
  \settototalheight{\@gsheadboxheight}{\usebox{\@gsheadbox}}%
}

\RequirePackage{alphalph}
\newalphalph{\fnsymbolmult}[mult]{\@fnsymbol}{5}

\newcounter{authorfn}
\setcounter{authorfn}{1}
\newcommand{\authfn}[1]{%
  \fnsymbolmult{#1}%
}

\renewcommand\Authands{ and }
\renewcommand\AB@affilsepx{ and }
\renewcommand{\Authfont}{\fontsize{13pt}{18pt}\selectfont}
\renewcommand{\Affilfont}{\fontsize{9pt}{13pt}\selectfont}
\setlength{\affilsep}{21pt-9pt}

\AtBeginDocument{
\renewcommand{\@maketitle}{%
  \textblockorigin{4pc+6.64pt}{4pc+6pt}
  %%%%
  \begin{textblock*}{21pc}(0pt,0pt)
  \IfFileExists{\@upflogo}{%
    \includegraphics[height=\@gsheadboxheight]{\@upflogo}%
  }{%
    \fbox{\begin{minipage}[b][\@gsheadboxheight]{\@gsheadboxheight}
    \raggedright
    Placeholder for UPF Editora logo \@upflogo
    \end{minipage}}%
  }
  \hspace{12pt}%
  %% Do absolutely nothing if \@jlogo is empty string
  \ifdefempty{\@jlogo}{}{%
  \IfFileExists{\@jlogo}{%
    \includegraphics[height=\@gscitedetailsheight]{\@jlogo}
  }{%
    \fbox{\begin{minipage}[b][\@gsheadboxheight]{\@gsheadboxheight}%
    \raggedright Placeholder for RBCA logo \@jlogo
    \end{minipage}}%
  }}
  \end{textblock*}
  %%%
  \begin{textblock*}{\textwidth-21pc}(21pc,0pt)
  \usebox{\@gsheadbox}
  \end{textblock*}%
  %%%
  \null\vspace*{\dimexpr 13pc+11pt-5pc-6pt\relax}%
  \raggedright%
  {\fontsize{10pt}{16pt}\selectfont%
    \ifpdf
      \textls[200]{\textbf{\MakeUppercase{\@papercat}}}
    \else %%% don't use letterspace in latex+dvi
      \textbf{\MakeUppercase{\@papercat}}%
    \fi%
    \par}
  \vspace{\dimexpr 26pt-18pt\relax}
  {\centering\fontsize{16pt}{27pt}\bfseries\color{jcolour}\@title\par}
  \vspace{\dimexpr 26pt-13pt\relax}
  \centering{\@author}\par
  \vspace{\dimexpr 15.5pt-1em}
  {%
    \renewcommand{\authfn}[1]{%
    \textsuperscript{\fnsymbolmult{##1}}%
    }
    {\fontsize{8pt}{9.5pt}\selectfont\@authnotes\par}%
    \vspace{\dimexpr 15.5pt-1em}
    \textbf{Received:} \@jrec. \textbf{Revised:} \@jrec.    \textbf{Accepted:} \@jrec.\par%
    {\noindent\color{jcolour}\rule{\hsize}{3pt}}\par%
  }
  \vspace{\dimexpr 16pt-3pt-1em\relax}
}
}

\RequirePackage[style]{abstract}
\setlength{\absleftindent}{0pt}
\setlength{\absrightindent}{0pt}
\setlength{\absparindent}{12pt}
\setlength{\absparsep}{0pt}
\setlength{\abstitleskip}{16pt-8pt-\baselineskip}
\renewcommand{\abstractnamefont}{\fontsize{11pt}{12pt}\bfseries\color{jcolour}}
\renewcommand{\abstitlestyle}[1]{{\abstractnamefont #1}}
\renewcommand{\abstracttextfont}{\fontsize{9pt}{11pt}\selectfont}

\preto{\abstract}{%
  \vspace*{\dimexpr 23pt-10pt\relax}
}
\appto\abstract{\noindent\ignorespaces}
\preto\endabstract{\par}

\newenvironment{Abstract}{
	\def\abstractname{Abstract}
	\begin{abstract}
	}{
	\end{abstract}
}

\newenvironment{resumo}{
	\def\abstractname{Resumo}
	\begin{abstract}
	}{
	\end{abstract}
}

\newenvironment{keywords}
{\vspace*{\dimexpr 19pt-8pt-\baselineskip\relax}%
\noindent\fontsize{9pt}{11pt}\selectfont\textbf{Key words}: \ignorespaces}%
{\par}{\par}

\newenvironment{palavras_chave}
{\vspace*{\dimexpr 19pt-8pt-\baselineskip\relax}%
	\noindent\fontsize{9pt}{11pt}\selectfont\textbf{Palavras-Chave}: \ignorespaces}%
{\par}

\if@twocolumn
  \NewEnviron{frontmatter}
  {\twocolumn[%
      \BODY%
      \vspace*{\dimexpr 16pt-3pt-1em\relax}
      {\noindent\color{jcolour}\rule{\hsize}{3pt}}\par
      \vspace*{\dimexpr 23pt-1em\relax}]%
  }
\else
  \NewEnviron{frontmatter}{%
      \BODY%
      \vspace*{\dimexpr 16pt-3pt-1em\relax}
      {\noindent\color{jcolour}\rule{\hsize+4pc+6.64pt}{3pt}}\par
      \vspace*{\dimexpr 23pt-1em\relax}%
  }
\fi

\setcounter{secnumdepth}{4}
\titleformat*{\section}{\fontsize{11pt}{12pt}\bfseries\color{jcolour}}
\titlespacing*{\section}{0pt}{26.5pt-1em}{16pt-1em}

\titleformat*{\subsection}{\fontsize{10pt}{11pt}\bfseries\color{jcolour}}
\titlespacing*{\subsection}{0pt}{2pc-1em}{17pt-1em}

\titleformat*{\subsubsection}{\fontsize{9pt}{11pt}\bfseries\slshape\color{jcolour}}
\titlespacing*{\subsubsection}{0pt}{\baselineskip}{0pt}

\titleformat{\paragraph}[runin]{\color{jcolour}\fontsize{9pt}{11pt}\itshape}{\theparagraph}{5pt}{}[.\enspace]
\titlespacing*{\paragraph}{0pt}{\baselineskip}{0pt}

\RequirePackage{enumitem}
\setlist{noitemsep}
\setlist[itemize]{leftmargin=12pt,topsep=16pt-1em}
\setlist[enumerate]
{itemindent=14pt,topsep=16.8pt-1em,
 label={\roman*.},labelsep=7pt,
 labelwidth=*,leftmargin=*,align=right}


% quotes and epigraphs
\RequirePackage{quoting}
\newcommand{\quotefont}{\fontsize{6.5pt}{9.5pt}\selectfont}
\quotingsetup{vskip=16pt-1em,indentfirst=false,font={quotefont},leftmargin=12pt,rightmargin=12pt}

\renewenvironment{quote}{\begin{quoting}}{\end{quoting}}

\renewenvironment{quotation}{\begin{quoting}}{\end{quoting}}

\newenvironment{epigraph}[1]
{\begin{quoting}[font={itshape,fontsize{7.5pt}{10.5pt}},vskip=15pt-1em,leftmargin=0pt,rightmargin=0pt]%
 \def\@quotesource{#1}}
{\par\vspace{\dimexpr 15pt-1em\relax}{\upshape---\@quotesource}\end{quoting}}

% Space above/below equations
\g@addto@macro\normalsize{%
  \setlength\abovedisplayskip{\baselineskip}%
  \setlength\belowdisplayskip{\baselineskip}%
  \setlength\abovedisplayshortskip{\baselineskip}%
  \setlength\belowdisplayshortskip{\baselineskip}%
}

\RequirePackage{stfloats}
\RequirePackage{booktabs}
\RequirePackage{tabularx}
% Left-, right- and center-aligned auto-wrapping column types
\newcolumntype{L}{>{\raggedright\arraybackslash}X}
\newcolumntype{R}{>{\raggedleft\arraybackslash}X}
\newcolumntype{C}{>{\centering\arraybackslash}X}

\AtBeginEnvironment{tabularx}{%
  \fontsize{8pt}{10pt}\selectfont
}
\AtBeginEnvironment{tabular}{%
  \fontsize{8pt}{10pt}\selectfont
}

\setlength{\aboverulesep}{11pt-1em}
\setlength{\belowrulesep}{11pt-1em}
\setlength{\heavyrulewidth}{0.5pt}
\setlength{\lightrulewidth}{0.5pt}
\arrayrulecolor{jcolour}


\RequirePackage[tableposition=top]{caption}
\DeclareCaptionFont{figcaptionfont}{\fontsize{9pt}{9pt}\selectfont}
\DeclareCaptionFont{tabcaptionfont}{\fontsize{9pt}{9pt}\selectfont}
\captionsetup{justification=centering,singlelinecheck=false,labelfont={bf},labelsep=colon}
\captionsetup*[figure]{font=figcaptionfont,skip=10pt}
\captionsetup*[table]{font=tabcaptionfont,skip=10pt-1em}

% Skips for floats
\setlength{\floatsep}{1pc+6pt}
\setlength{\intextsep}{1pc+6pt}
\setlength{\textfloatsep}{1pc+6pt}

% References
\if@numrefs
  \RequirePackage[numbers]{natbib }
  \bibliographystyle{agsm}
\fi
\if@alpharefs
    \RequirePackage{natbib}
    \bibliographystyle{dcu}
\fi