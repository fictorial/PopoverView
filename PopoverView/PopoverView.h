//
//  PopoverView.h
//  Embark
//
//  Created by Oliver Rickard on 20/08/2012.
//
//

#import <UIKit/UIKit.h>
#import "PopoverViewCompatibility.h"


/**************** Support both ARC and non-ARC ********************/

#ifndef SUPPORT_ARC
#define SUPPORT_ARC

#if __has_feature(objc_arc_weak)                //objc_arc_weak
#define WEAK weak
#define __WEAK __weak
#define STRONG strong

#define AUTORELEASE self
#define RELEASE self
#define RETAIN self
#define CFTYPECAST(exp) (__bridge exp)
#define TYPECAST(exp) (__bridge_transfer exp)
#define CFRELEASE(exp) CFRelease(exp)
#define DEALLOC self

#elif __has_feature(objc_arc)                   //objc_arc
#define WEAK unsafe_unretained
#define __WEAK __unsafe_unretained
#define STRONG strong

#define AUTORELEASE self
#define RELEASE self
#define RETAIN self
#define CFTYPECAST(exp) (__bridge exp)
#define TYPECAST(exp) (__bridge_transfer exp)
#define CFRELEASE(exp) CFRelease(exp)
#define DEALLOC self

#else                                           //none
#define WEAK assign
#define __WEAK
#define STRONG retain

#define AUTORELEASE autorelease
#define RELEASE release
#define RETAIN retain
#define CFTYPECAST(exp) (exp)
#define TYPECAST(exp) (exp)
#define CFRELEASE(exp) CFRelease(exp)
#define DEALLOC dealloc

#endif
#endif

/******************************************************************/


@class PopoverView;

@protocol PopoverViewDelegate <NSObject>

@optional

//Delegate receives this call as soon as the item has been selected
- (void)popoverView:(PopoverView *)popoverView didSelectItemAtIndex:(NSInteger)index;

//Delegate receives this call once the popover has begun the dismissal animation
- (void)popoverViewDidDismiss:(PopoverView *)popoverView;

@end

@interface PopoverView : UIView {
    CGRect boxFrame;
    CGSize contentSize;
    CGPoint arrowPoint;
    
    BOOL above;
    
    __WEAK id<PopoverViewDelegate> delegate;
    
    UIView *parentView;
    
    UIView *topView;
    
    NSArray *subviewsArray;
    
    NSArray *dividerRects;
    
    UIView *contentView;
    
    UIView *titleView;
    
    UIActivityIndicatorView *activityIndicator;
    
    //Instance variable that can change at runtime
    BOOL showDividerRects;
}

@property (nonatomic, STRONG) UIView *titleView;

@property (nonatomic, STRONG) UIView *contentView;

@property (nonatomic, STRONG) NSArray *subviewsArray;

@property (nonatomic, WEAK) id<PopoverViewDelegate> delegate;

#pragma mark - Appearance

//Height/width of the actual arrow
@property (nonatomic) CGFloat arrowHeight UI_APPEARANCE_SELECTOR;

//padding within the box for the contentView
@property (nonatomic) CGFloat boxPadding UI_APPEARANCE_SELECTOR;

//control point offset for rounding corners of the main popover box
@property (nonatomic) CGFloat CPOffset UI_APPEARANCE_SELECTOR;

//radius for the rounded corners of the main popover box
@property (nonatomic) CGFloat boxRadius UI_APPEARANCE_SELECTOR;

//Curvature value for the arrow.  Set to 0.f to make it linear.
@property (nonatomic) CGFloat arrowCurvature UI_APPEARANCE_SELECTOR;

//Minimum distance from the side of the arrow to the beginning of curvature for the box
@property (nonatomic) CGFloat arrowHorizontalPadding UI_APPEARANCE_SELECTOR;

//Alpha value for the shadow behind the PopoverView
@property (nonatomic) CGFloat shadowAlpha UI_APPEARANCE_SELECTOR;

//Blur for the shadow behind the PopoverView
@property (nonatomic) CGFloat shadowBlur UI_APPEARANCE_SELECTOR;

//Box gradient bg alpha
@property (nonatomic) CGFloat boxAlpha UI_APPEARANCE_SELECTOR;

//Padding along top of screen to allow for any nav/status bars
@property (nonatomic) CGFloat topMargin UI_APPEARANCE_SELECTOR;

//margin along the left and right of the box
@property (nonatomic) CGFloat horizontalMargin UI_APPEARANCE_SELECTOR;

//padding along top of icons/images
@property (nonatomic) CGFloat imageTopPadding UI_APPEARANCE_SELECTOR;

//padding along bottom of icons/images
@property (nonatomic) CGFloat imageBottomPadding UI_APPEARANCE_SELECTOR;

// show popover arrow
@property (nonatomic) NSInteger showArrow UI_APPEARANCE_SELECTOR;

// DIVIDERS BETWEEN VIEWS

//Bool that turns off/on the dividers
@property (nonatomic) NSInteger showDividersBetweenViews UI_APPEARANCE_SELECTOR;

//color for the divider fill
@property (nonatomic, STRONG) UIColor *dividerColor UI_APPEARANCE_SELECTOR;


// BACKGROUND GRADIENT

//bottom color white in gradient bg
@property (nonatomic, STRONG) UIColor *gradientBottomColor UI_APPEARANCE_SELECTOR;

//top color white value in gradient bg
@property (nonatomic, STRONG) UIColor *gradientTopColor UI_APPEARANCE_SELECTOR;


// TITLE GRADIENT

//bool that turns off/on title gradient
@property (nonatomic) NSInteger drawTitleGradient UI_APPEARANCE_SELECTOR;

//bottom color white value in title gradient bg
@property (nonatomic, STRONG) UIColor *gradientTitleBottomColor UI_APPEARANCE_SELECTOR;

//top color white value in title gradient bg
@property (nonatomic, STRONG) UIColor *gradientTitleTopColor UI_APPEARANCE_SELECTOR;


// FONTS

//normal text font
@property (nonatomic, STRONG) UIFont *textFont UI_APPEARANCE_SELECTOR;

//normal text color
@property (nonatomic, STRONG) UIColor *textColor UI_APPEARANCE_SELECTOR;

// highlighted text color
@property (nonatomic, STRONG) UIColor *textHighlightColor UI_APPEARANCE_SELECTOR;

//normal text alignment
@property (nonatomic) UITextAlignment textAlignment UI_APPEARANCE_SELECTOR;

//title font
@property (nonatomic, STRONG) UIFont *titleFont UI_APPEARANCE_SELECTOR;

//title text color
@property (nonatomic, STRONG) UIColor *titleColor UI_APPEARANCE_SELECTOR;


// BORDER

//bool that turns off/on the border
@property (nonatomic) NSInteger drawBorder UI_APPEARANCE_SELECTOR;

//border color
@property (nonatomic, STRONG) UIColor *borderColor UI_APPEARANCE_SELECTOR;

//border width
@property (nonatomic) CGFloat borderWidth UI_APPEARANCE_SELECTOR;

#pragma mark - Class Static Showing Methods

//These are the main static methods you can use to display the popover.
//Simply call [PopoverView show...] with your arguments, and the popover will be generated, added to the view stack, and notify you when it's done.

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withText:(NSString *)text delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withText:(NSString *)text delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withViewArray:(NSArray *)viewArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withViewArray:(NSArray *)viewArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withStringArray:(NSArray *)stringArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withStringArray:(NSArray *)stringArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withStringArray:(NSArray *)stringArray withImageArray:(NSArray *)imageArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withStringArray:(NSArray *)stringArray withImageArray:(NSArray *)imageArray delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withContentView:(UIView *)cView delegate:(id<PopoverViewDelegate>)delegate;

+ (PopoverView *)showPopoverAtPoint:(CGPoint)point inView:(UIView *)view withContentView:(UIView *)cView delegate:(id<PopoverViewDelegate>)delegate;

#pragma mark - Instance Showing Methods

//Adds/animates in the popover to the top of the view stack with the arrow pointing at the "point"
//within the specified view.  The contentView will be added to the popover, and should have either
//a clear color backgroundColor, or perhaps a rounded corner bg rect (radius 4.f if you're going to
//round).
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withContentView:(UIView *)contentView;

//Calls above method with a UILabel containing the text you deliver to this method.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withText:(NSString *)text;

//Calls top method with an array of UIView objects.  This method will stack these views vertically
//with kBoxPadding padding between each view in the y-direction.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withViewArray:(NSArray *)viewArray;

//Does same as above, but adds a title label at top of the popover.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withViewArray:(NSArray *)viewArray;

//Calls the viewArray method with an array of UILabels created with the strings
//in stringArray.  All contents of stringArray must be NSStrings.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withStringArray:(NSArray *)stringArray;

//This method does same as above, but with a title label at the top of the popover.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withStringArray:(NSArray *)stringArray;

//Draws a vertical list of the NSString elements of stringArray with UIImages
//from imageArray placed centered above them.
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withStringArray:(NSArray *)stringArray withImageArray:(NSArray *)imageArray;

//Does the same as above, but with a title
- (void)showAtPoint:(CGPoint)point inView:(UIView *)view withTitle:(NSString *)title withStringArray:(NSArray *)stringArray withImageArray:(NSArray *)imageArray;

//Lays out the PopoverView at a point once all of the views have already been setup elsewhere
- (void)layoutAtPoint:(CGPoint)point inView:(UIView *)view;

#pragma mark - Other Interaction
//This method animates the rotation of the PopoverView to a new point
- (void)animateRotationToNewPoint:(CGPoint)point inView:(UIView *)view withDuration:(NSTimeInterval)duration;

#pragma mark - Dismissal
//Dismisses the view, and removes it from the view stack.
- (void)dismiss;
- (void)dismiss:(BOOL)animated;

#pragma mark - Activity Indicator Methods

//Shows the activity indicator, and changes the title (if the title is available, and is a UILabel).
- (void)showActivityIndicatorWithMessage:(NSString *)msg;

//Hides the activity indicator, and changes the title (if the title is available) to the msg
- (void)hideActivityIndicatorWithMessage:(NSString *)msg;

#pragma mark - Custom Image Showing

//Animate in, and display the image provided here.
- (void)showImage:(UIImage *)image withMessage:(NSString *)msg;

#pragma mark - Error/Success Methods

//Shows (and animates in) an error X in the contentView
- (void)showError;

//Shows (and animates in) a success checkmark in the contentView
- (void)showSuccess;

@end
