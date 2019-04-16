#include "Entity.h"

int Entity::currentID = 0;

void Entity::OnSetPosition(D3DXVECTOR3 pos) {
}

Entity::Entity() {
	tag = None;
	id = ++currentID;
}

RECT Entity::GetBound() {
	RECT r;
	r.left = position.x - width / 2;
	r.top = position.y - height / 2;
	r.right = r.left + width;
	r.bottom = r.top + height;
	return r;
}

Entity::EntityTypes Entity::GetTag() {
	return tag;
}

void Entity::SetTag(EntityTypes tag) {
	this->tag = tag;
}


void Entity::SetPosition(float x, float y) {
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::SetPosition(D3DXVECTOR2 pos) {
	SetPosition(D3DXVECTOR3(pos));
}

void Entity::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
	OnSetPosition(position);
}

void Entity::AddPosition(D3DXVECTOR3 pos) {
	SetPosition(pos + position);
}

void Entity::AddPosition(D3DXVECTOR2 pos) {
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y) {
	AddPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR3 Entity::GetPosition() {
	return position;
}

void Entity::SetWidth(int width) {
	this->width = width;
}

int Entity::GetWidth() {
	return width;
}

void Entity::SetHeight(int height) {
	this->height = height;
}

int Entity::GetHeight() {
	return height;
}

void Entity::SetVelocity(D3DXVECTOR2 vel) {
	velocity = vel;
}

D3DXVECTOR2 Entity::GetVelocity() {
	return velocity;
}

float Entity::GetVx(){
	return velocity.x;
}

void Entity::SetVx(float vx) {
	this->velocity.x = vx;
}

void Entity::AddVx(float vx) {
	this->velocity.x += vx;
}

float Entity::GetVy() {
	return velocity.y;
}

void Entity::SetVy(float vy) {
	this->velocity.y = vy;
}

void Entity::AddVy(float vy) {
	this->velocity.y += vy;
}

int Entity::GetID() {
	return id;
}

void Entity::Update(double dt) {
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Entity::OnCollision(Entity * impactor, CollisionReturn data, SideCollision side) {
	velocity = D3DXVECTOR2(0, 0);
}
